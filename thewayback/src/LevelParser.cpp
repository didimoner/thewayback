#include "pch.h"
#include <zlib.h>
#include "vendor/base64.h"
#include "LevelParser.h"
#include "SystemUtils.h"
#include "TextureManager.h"
#include "Game.h"
#include "Level.h"
#include "Tileset.h"
#include "Log.h"
#include "TileLayer.h"
#include "ObstacleLayer.h"
#include "Animation.h"
#include "Player.h"
#include "GameObjectFactory.h"
#include "Obstacle.h"

using namespace tinyxml2;

Log LevelParser::Logger(typeid(LevelParser).name());

std::unique_ptr<Level> LevelParser::parse(const std::string& filename) {
    Logger.debug("Loading level from " + filename);

    const std::string resourcesPath = getResourcePath("maps");
    const std::string filepath = resourcesPath + filename;

    XMLDocument xmlDoc(true, COLLAPSE_WHITESPACE);

    XMLError loadResult = xmlDoc.LoadFile(filepath.c_str());
    if (loadResult != XML_SUCCESS) {
        Logger.error("Cannot load " + filename);
        return nullptr;
    }

    XMLElement* pRoot = xmlDoc.FirstChildElement();
    if (pRoot == nullptr) {
        Logger.warn("No root element found in " + filename);
        return nullptr;
    }

    std::unique_ptr<Level> pLevel = std::unique_ptr<Level>(new Level);
    pLevel->m_width = pRoot->IntAttribute("width");
    pLevel->m_height = pRoot->IntAttribute("height");
    pLevel->m_tileWidth = pRoot->IntAttribute("tilewidth");
    pLevel->m_tileHeight = pRoot->IntAttribute("tileheight");

    parseMapProps(pRoot);
    parseTilesets(pRoot, *pLevel);
    parseTileLayers(pRoot, *pLevel);
    parseObjectLayers(pRoot, *pLevel);

    return pLevel;
}

void LevelParser::parseMapProps(XMLElement* pPropsRoot) {
    XMLElement* pPropsElement = pPropsRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        const std::string textureId = p->Attribute("name");
        const std::string filename = p->Attribute("value");

        TextureManager::instance().load(filename, textureId, Game::instance().getRenderer());
    }
}

void LevelParser::parseTilesets(XMLElement* pTilesetsRoot, Level& level) {
    for (XMLElement* e = pTilesetsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("tileset")) {
            continue;
        }

        Tileset tileset;
        tileset.firstGlobalId = e->IntAttribute("firstgid");
        tileset.tileWidth = e->IntAttribute("tilewidth");
        tileset.tileHeight = e->IntAttribute("tileheight");
        tileset.tileCount = e->IntAttribute("tilecount");
        tileset.columns = e->IntAttribute("columns");
        tileset.name = e->Attribute("name");
        level.getTilesets().push_back(std::move(tileset));

        XMLElement* pImageElement = e->FirstChildElement("image");
        const std::string source = pImageElement->Attribute("source");
        const std::string filename = splitString(source, '/').back();
        TextureManager::instance().load(filename, e->Attribute("name"), Game::instance().getRenderer());
    }
}

void LevelParser::parseTileLayers(XMLElement* pLayerRoot, Level& level) {
    for (XMLElement* e = pLayerRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("layer")) {
            continue;
        }

        XMLElement* pDataElement = e->FirstChildElement("data");
        if (pDataElement == nullptr) {
            continue;
        }

        const std::string textData = pDataElement->GetText();
        const std::string decodedData = base64_decode(textData);
        uLongf allTilesSize = level.m_width * level.m_height * sizeof(int);
        const std::vector<uint32_t> uncompressedTileIds(allTilesSize);

        const int uncompressStatus = uncompress((Bytef*)&uncompressedTileIds[0], &allTilesSize,
                                                (const Bytef*)decodedData.c_str(), decodedData.size());
        if (uncompressStatus != Z_OK) {
            Logger.warn("Something wrong with zlib uncpompression. Code: " + uncompressStatus);
        }

        std::vector<std::vector<uint32_t>> tileIds;
        for (uint32_t i = 0; i < level.m_height; i++) {
            tileIds.emplace_back(level.m_width);
        }

        for (uint32_t row = 0; row < level.m_height; row++) {
            for (uint32_t column = 0; column < level.m_width; column++) {
                tileIds[row][column] = uncompressedTileIds[row * level.m_width + column];
            }
        }

        std::shared_ptr<TileLayer> pTileLayer = std::make_shared<TileLayer>(level.getTilesets());
        pTileLayer->setPriority(e->IntAttribute("id"));
        pTileLayer->setName(e->Attribute("name"));
        pTileLayer->setTileIds(tileIds);
        level.getDrawables().insert(pTileLayer);
    }
}

void LevelParser::parseObjectLayers(XMLElement* pObjectsRoot, Level& level) {
    for (XMLElement* e = pObjectsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("objectgroup")) {
            continue;
        }

        std::string layerType = getStringProperty(e, "type");
        if (layerType == "obstacles") {
            parseObstacles(e, level);
        } else if (layerType == "game_objects") {
            parseGameObjects(e, level);
        }
    }
}

void LevelParser::parseObstacles(XMLElement* pRoot, Level& level) {
    const std::string layerId = pRoot->Attribute("name");
    const uint8_t gridCols = getIntProperty(pRoot, "grid_cols");
    const uint8_t gridRows = getIntProperty(pRoot, "grid_rows");

    std::unique_ptr<ObstacleLayer> pObstacleLayer = std::make_unique<ObstacleLayer>(
        layerId,
        level.m_width * level.m_tileWidth,
        level.m_height * level.m_tileHeight,
        gridCols, gridRows
    );

    for (XMLElement* o = pRoot->FirstChildElement("object"); o != nullptr; o = o->NextSiblingElement()) {
        std::shared_ptr<Obstacle> pObstacle = std::make_shared<Obstacle>(
            static_cast<float>(o->IntAttribute("x")), static_cast<float>(o->IntAttribute("y")),
            o->IntAttribute("width"), o->IntAttribute("height")
        );
        pObstacleLayer->addObstacle(pObstacle);
    }

    level.getObstacleLayers().push_back(std::move(pObstacleLayer));
}

void LevelParser::parseGameObjects(XMLElement* pRoot, Level& level) {
    for (XMLElement* o = pRoot->FirstChildElement("object"); o != nullptr; o = o->NextSiblingElement()) {
        const int x = o->IntAttribute("x");
        const int y = o->IntAttribute("y");
        const int width = o->IntAttribute("width");
        const int height = o->IntAttribute("height");
        std::string type = o->Attribute("type");
        const bool animated = getBoolProperty(o, "animated");
        const std::string textureId = getStringProperty(o, "textureId");

        std::shared_ptr<Sprite> pSprite = std::dynamic_pointer_cast<Sprite>(GameObjectFactory::instance().create(type));
        pSprite->setPriority(pRoot->IntAttribute("id"));

        if (animated) {
            AnimationInitParams animationInitParams;
            animationInitParams.speed = getIntProperty(o, "animationSpeed");
            animationInitParams.totalFrames = getIntProperty(o, "animationTotalFrames");
            animationInitParams.defaultFrame = getIntProperty(o, "animationDefaultFrame");
            if (getStringProperty(o, "animationType") == "BOUNCE") {
                animationInitParams.type = EAnimationType::BOUNCE;
            } else {
                animationInitParams.type = EAnimationType::NORMAL;
            }

            std::dynamic_pointer_cast<Animation>(pSprite)->init(static_cast<float>(x), static_cast<float>(y),
                width, height, textureId, animationInitParams);
        } else {
            pSprite->init(static_cast<float>(x), static_cast<float>(y), width, height, textureId);
        }

        if (type == "player" && !level.m_pPlayer) {
            std::shared_ptr<Player> pPlayer = std::dynamic_pointer_cast<Player>(pSprite);
            pPlayer->setWalkingSpeed(getFloatProperty(o, "walkingSpeed"));
            pPlayer->setRunningSpeed(getFloatProperty(o, "runningSpeed"));

            level.m_pPlayer = pPlayer;
            level.getDrawables().insert(pPlayer);
        }

        // todo: other game object types
    }
}

std::string LevelParser::getStringProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropsElement = pElementRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        if (p->Attribute("name") == name) {
            return p->Attribute("value");
        }
    }

    Logger.warn("There is no string property of name " + name);
    return "";
}

int LevelParser::getIntProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropsElement = pElementRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        if (p->Attribute("name") == name) {
            return p->IntAttribute("value");
        }
    }

    Logger.warn("There is no int property of name " + name);
    return 0;
}

auto LevelParser::getFloatProperty(XMLElement* pElementRoot, const std::string& name) -> float {
    XMLElement* pPropsElement = pElementRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        if (p->Attribute("name") == name) {
            return p->FloatAttribute("value");
        }
    }

    Logger.warn("There is no float property of name " + name);
    return 0;
}

auto LevelParser::getBoolProperty(XMLElement* pElementRoot, std::string name) -> bool {
    XMLElement* pPropsElement = pElementRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        if (p->Attribute("name") == name) {
            return p->BoolAttribute("value");
        }
    }

    Logger.warn("There is no bool property of name " + name);
    return false;
}
