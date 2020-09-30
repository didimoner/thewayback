#include "pch.h"
#include <zlib.h>
#include <SDL_rect.h>
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

Log LevelParser::Logger(typeid(LevelParser).name());

Level* LevelParser::parse(std::string filename) {
    Logger.debug("Loading level from " + filename);

    std::string resourcesPath = getResourcePath("maps");
    std::string filepath = resourcesPath + filename;

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

    Level* pLevel = new Level();
    pLevel->m_width = pRoot->IntAttribute("width");
    pLevel->m_height = pRoot->IntAttribute("height");
    pLevel->m_tileWidth = pRoot->IntAttribute("tilewidth");
    pLevel->m_tileHeight = pRoot->IntAttribute("tileheight");

    parseMapProps(pRoot);
    parseTilesets(pRoot, pLevel->getTilesets());
    parseTileLayers(pRoot, pLevel);
    parseObjectLayers(pRoot, pLevel);

    return pLevel;
}

void LevelParser::parseMapProps(XMLElement* pPropsRoot) {
    XMLElement* pPropsElement = pPropsRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        std::string textureId = p->Attribute("name");
        std::string filename = p->Attribute("value");

        TextureManager::instance().load(filename, textureId, Game::instance().getRenderer());
    }
}

void LevelParser::parseTilesets(XMLElement* pTilesetsRoot, std::vector<Tileset>* pTilesets) {
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
        pTilesets->push_back(tileset);

        XMLElement* pImageElement = e->FirstChildElement("image");
        std::string filename = splitString(pImageElement->Attribute("source"), '/').back();
        TextureManager::instance().load(filename, tileset.name, Game::instance().getRenderer());
    }
}

void LevelParser::parseTileLayers(XMLElement* pLayerRoot, Level* pLevel) {
    for (XMLElement* e = pLayerRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("layer")) {
            continue;
        }

        XMLElement* pDataElement = e->FirstChildElement("data");
        if (pDataElement == nullptr) {
            continue;
        }

        std::string textData = pDataElement->GetText();

        std::string decodedData = base64_decode(textData);
        uLongf allTilesSize = pLevel->m_width * pLevel->m_height * sizeof(int);
        std::vector<uint32_t> uncompressedTileIds(allTilesSize);

        int uncompressStatus = uncompress((Bytef*)&uncompressedTileIds[0], &allTilesSize,
                                          (const Bytef*)decodedData.c_str(), decodedData.size());
        if (uncompressStatus != Z_OK) {
            Logger.warn("Something wrong with zlib uncpompression. Code: " + uncompressStatus);
        }

        std::vector<std::vector<uint32_t>> tileIds;
        for (uint32_t i = 0; i < pLevel->m_height; i++) {
            tileIds.push_back(std::vector<uint32_t>(pLevel->m_width));
        }

        for (uint32_t row = 0; row < pLevel->m_height; row++) {
            for (uint32_t column = 0; column < pLevel->m_width; column++) {
                tileIds[row][column] = uncompressedTileIds[row * pLevel->m_width + column];
            }
        }

        TileLayer* pTileLayer = new TileLayer(*pLevel->getTilesets());
        pTileLayer->setPriority(e->IntAttribute("id"));
        pTileLayer->setName(e->Attribute("name"));
        pTileLayer->setTileIds(tileIds);

        pLevel->getDrawables()->insert(pTileLayer);
    }
}

void LevelParser::parseObjectLayers(XMLElement* pObjectsRoot, Level* pLevel) {
    for (XMLElement* e = pObjectsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("objectgroup")) {
            continue;
        }

        std::string layerType = getStringProperty(e, "type");
        if (layerType == "obstacles") {
            parseObstacles(e, pLevel);
        } else if (layerType == "game_objects") {
            parseGameObjects(e, pLevel);
        }
    }

}

void LevelParser::parseObstacles(XMLElement* pRoot, Level* pLevel) {
    std::string layerId = pRoot->Attribute("name");
    uint8_t gridCols = getIntProperty(pRoot, "grid_cols");
    uint8_t gridRows = getIntProperty(pRoot, "grid_rows");
    ObstacleLayer* pCollidableLayer = new ObstacleLayer(
        layerId,
        pLevel->m_width * pLevel->m_tileWidth,
        pLevel->m_height * pLevel->m_tileHeight,
        gridCols, gridRows
    );

    for (XMLElement* o = pRoot->FirstChildElement("object"); o != nullptr; o = o->NextSiblingElement()) {
        Obstacle* pObstacle = new Obstacle(
            static_cast<float>(o->IntAttribute("x")), static_cast<float>(o->IntAttribute("y")),
            o->IntAttribute("width"), o->IntAttribute("height")
        );

        pCollidableLayer->addObstacle(pObstacle);
    }

    pLevel->getObstacleLayers()->push_back(pCollidableLayer);
}

void LevelParser::parseGameObjects(XMLElement* pRoot, Level* pLevel) {
    for (XMLElement* o = pRoot->FirstChildElement("object"); o != nullptr; o = o->NextSiblingElement()) {
        int x = o->IntAttribute("x");
        int y = o->IntAttribute("y");
        int width = o->IntAttribute("width");
        int height = o->IntAttribute("height");
        std::string type = o->Attribute("type");
        bool animated = getBoolProperty(o, "animated");
        std::string textureId = getStringProperty(o, "textureId");

        Sprite* sprite = static_cast<Sprite*>(GameObjectFactory::instance().create(type));
        sprite->setPriority(pRoot->IntAttribute("id"));

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

            static_cast<Animation*>(sprite)->init(static_cast<float>(x), static_cast<float>(y), width, height, textureId,
                                                  animationInitParams);
        } else {
            sprite->init(static_cast<float>(x), static_cast<float>(y), width, height, textureId);
        }

        if (type == "player" && pLevel->m_pPlayer == nullptr) {
            Player* pPlayer = static_cast<Player*>(sprite);
            pPlayer->setWalkingSpeed(getFloatProperty(o, "walkingSpeed"));
            pPlayer->setRunningSpeed(getFloatProperty(o, "runningSpeed"));

            pLevel->m_pPlayer = pPlayer;
            pLevel->getDrawables()->insert(pPlayer);
        }

        // todo: other game object types
    }
}

std::string LevelParser::getStringProperty(XMLElement* pElementRoot, std::string name) const {
    XMLElement* pPropsElement = pElementRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        if (p->Attribute("name") == name) {
            return p->Attribute("value");
        }
    }

    Logger.warn("There is no string property of name " + name);
    return "";
}

int LevelParser::getIntProperty(XMLElement* pElementRoot, std::string name) const {
    XMLElement* pPropsElement = pElementRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        if (p->Attribute("name") == name) {
            return p->IntAttribute("value");
        }
    }

    Logger.warn("There is no int property of name " + name);
    return 0;
}

float LevelParser::getFloatProperty(XMLElement* pElementRoot, std::string name) const {
    XMLElement* pPropsElement = pElementRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        if (p->Attribute("name") == name) {
            return p->FloatAttribute("value");
        }
    }

    Logger.warn("There is no float property of name " + name);
    return 0;
}

bool LevelParser::getBoolProperty(XMLElement* pElementRoot, std::string name) const {
    XMLElement* pPropsElement = pElementRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        if (p->Attribute("name") == name) {
            return p->BoolAttribute("value");
        }
    }

    Logger.warn("There is no bool property of name " + name);
    return false;
}
