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
#include "Obstacle.h"
#include "XmlHelper.h"

using namespace tinyxml2;

Log LevelParser::Logger(typeid(LevelParser).name());

std::shared_ptr<Level> LevelParser::parse(const std::string& filename) {
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

    auto pLevel = std::shared_ptr<Level>(new Level);
    pLevel->m_id = filename;
    pLevel->m_width = pRoot->UnsignedAttribute("width");
    pLevel->m_height = pRoot->UnsignedAttribute("height");
    pLevel->m_tileWidth = pRoot->UnsignedAttribute("tilewidth");
    pLevel->m_tileHeight = pRoot->UnsignedAttribute("tileheight");

    parseTilesets(pRoot, *pLevel);
    parseTileLayers(pRoot, pLevel);
    parseObjectLayers(pRoot, *pLevel);

    return pLevel;
}

void LevelParser::parseTilesets(XMLElement* pTilesetsRoot, Level& level) {
    for (XMLElement* e = pTilesetsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("tileset")) {
            continue;
        }

        Tileset tileset;
        tileset.firstGlobalId = e->UnsignedAttribute("firstgid");
        tileset.tileWidth = e->UnsignedAttribute("tilewidth");
        tileset.tileHeight = e->UnsignedAttribute("tileheight");
        tileset.tileCount = e->UnsignedAttribute("tilecount");
        tileset.columns = e->UnsignedAttribute("columns");
        tileset.name = e->Attribute("name");
        level.m_tilesets.push_back(std::move(tileset));

        XMLElement* pImageElement = e->FirstChildElement("image");
        const std::string source = pImageElement->Attribute("source");
        const std::string filename = splitString(source, '/').back();
        TextureManager::instance().load(filename, e->Attribute("name"));
    }
}

void LevelParser::parseTileLayers(XMLElement* pLayerRoot, const std::shared_ptr<Level>& pLevel) {
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
        uLongf allTilesSize = pLevel->m_width * pLevel->m_height * sizeof(int);
        const std::vector<uint32_t> uncompressedTileIds(allTilesSize);

        const int uncompressStatus = uncompress((Bytef*)&uncompressedTileIds[0], &allTilesSize,
                                                (const Bytef*)decodedData.c_str(), decodedData.size());
        if (uncompressStatus != Z_OK) {
            Logger.warn("Something wrong with zlib uncpompression. Code: " + uncompressStatus);
        }

        std::vector<std::vector<uint32_t>> tileIds;
        for (uint32_t i = 0; i < pLevel->m_height; i++) {
            tileIds.emplace_back(pLevel->m_width);
        }

        for (uint32_t row = 0; row < pLevel->m_height; row++) {
            for (uint32_t column = 0; column < pLevel->m_width; column++) {
                tileIds[row][column] = uncompressedTileIds[row * pLevel->m_width + column];
            }
        }

        std::shared_ptr<TileLayer> pTileLayer = std::make_shared<TileLayer>(pLevel);
        pTileLayer->setPriority(e->UnsignedAttribute("id"));
        pTileLayer->setName(e->Attribute("name"));
        pTileLayer->setTileIds(tileIds);
        pLevel->m_drawableLayers.emplace(std::make_pair(pTileLayer->getPriority(), pTileLayer));
    }
}

void LevelParser::parseObjectLayers(XMLElement* pObjectsRoot, Level& level) {
    for (XMLElement* e = pObjectsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("objectgroup")) {
            continue;
        }

        std::string layerType = XmlHelper::getStringProperty(e, "type");
        if (layerType == "obstacles") {
            parseObstacles(e, level);
        } else if (layerType == "game_objects") {
            parseGameObjects(e, level);
        }
    }
}

void LevelParser::parseObstacles(XMLElement* pRoot, Level& level) {
    const std::string layerId = pRoot->Attribute("name");
    const uint8_t gridCols = XmlHelper::getUnsignedProperty(pRoot, "grid_cols");
    const uint8_t gridRows = XmlHelper::getUnsignedProperty(pRoot, "grid_rows");

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

    level.m_obstacleLayers.push_back(std::move(pObstacleLayer));
}

void LevelParser::parseGameObjects(XMLElement* pRoot, Level& level) {
    for (XMLElement* o = pRoot->FirstChildElement("object"); o != nullptr; o = o->NextSiblingElement()) {
        auto pGameObject = XmlHelper::parseGameObject(o);
        // todo: create layer of game objects
        // .insert(pGameObject);
    }
}