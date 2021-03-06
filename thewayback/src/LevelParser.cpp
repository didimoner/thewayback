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
#include "SolidObjectsGrid.h"
#include "Obstacle.h"
#include "Portal.h"
#include "XmlHelper.h"
#include "GameObjectParser.h"
#include "DialogParser.h"

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

void LevelParser::parseTilesets(XMLElement* pRoot, Level& level) {
    for (XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
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

void LevelParser::parseTileLayers(XMLElement* pRoot, const std::shared_ptr<Level>& pLevel) {
    for (XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("layer")) {
            continue;
        }

        XMLElement* pDataElement = e->FirstChildElement("data");
        if (pDataElement == nullptr) {
            continue;
        }

        const std::string textData = pDataElement->GetText();
        const std::string decodedData = base64_decode(textData);
        uLongf allTilesSize = pLevel->m_width * pLevel->m_height * sizeof(int32_t);
        const std::vector<uint32_t> uncompressedTileIds(allTilesSize);

        const int32_t uncompressStatus = uncompress((Bytef*)&uncompressedTileIds[0], &allTilesSize,
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
        pTileLayer->setZIndex(XmlHelper::getIntProperty(e, "zIndex"));
        pTileLayer->setName(e->Attribute("name"));
        pTileLayer->setTileIds(tileIds);
        pLevel->m_map.push_back(std::move(pTileLayer));
    }
}

void LevelParser::parseObjectLayers(XMLElement* pRoot, Level& level) {
    const uint8_t gridCols = XmlHelper::getUnsignedProperty(pRoot, "grid_cols");
    const uint8_t gridRows = XmlHelper::getUnsignedProperty(pRoot, "grid_rows");
    level.m_pSolidObjectsGrid = std::make_unique<SolidObjectsGrid>(
        level.m_width * level.m_tileWidth,
        level.m_height * level.m_tileHeight,
        gridCols, gridRows
    );

    for (XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("objectgroup")) {
            continue;
        }

        std::string layerType = XmlHelper::getStringProperty(e, "type");
        if (layerType == "obstacles") {
            parseObstacles(e, level);
        } else if (layerType == "portals") {
            parsePortals(e, level);
        } else if (layerType == "npc") {
            parseNpcs(e, level);
        }
    }
}

void LevelParser::parseObstacles(XMLElement* pObstaclesRoot, Level& level) {
    for (XMLElement* o = pObstaclesRoot->FirstChildElement("object"); o != nullptr; o = o->NextSiblingElement()) {
        std::shared_ptr<Obstacle> pObstacle = std::make_shared<Obstacle>(
            "obstacle",
            o->FloatAttribute("x"), o->FloatAttribute("y"),
            o->IntAttribute("width"), o->IntAttribute("height")
        );
        level.m_pSolidObjectsGrid->addObject(pObstacle);
    }
}

void LevelParser::parsePortals(XMLElement* pPortalsRoot, Level& level) {
    for (XMLElement* o = pPortalsRoot->FirstChildElement("object"); o != nullptr; o = o->NextSiblingElement()) {
        std::shared_ptr<Obstacle> pPortal = std::make_shared<Portal>(
            "portal",
            o->FloatAttribute("x"), o->FloatAttribute("y"),
            o->IntAttribute("width"), o->IntAttribute("height"),
            XmlHelper::getStringProperty(o, "levelId"),
            XmlHelper::getFloatProperty(o, "destX"), XmlHelper::getFloatProperty(o, "destY")
        );
        level.m_pSolidObjectsGrid->addObject(pPortal);
    }
}

void LevelParser::parseNpcs(XMLElement* pNpcsRoot, Level& level) {
    const int32_t zIndex = XmlHelper::getIntProperty(pNpcsRoot, "zIndex");
    for (XMLElement* o = pNpcsRoot->FirstChildElement("object"); o != nullptr; o = o->NextSiblingElement()) {
        auto pNpc = std::dynamic_pointer_cast<Npc>(GameObjectParser::parse(o));
        pNpc->setZIndex(zIndex);
        pNpc->setType("npc");
        
        const std::string dialogFile = XmlHelper::getStringProperty(o, "dialogFile");
        const auto dialogs = DialogParser::parse(dialogFile);
        pNpc->getDialogs().insert(std::end(pNpc->getDialogs()), std::begin(dialogs), std::end(dialogs));

        level.m_npcs.push_back(pNpc);
        level.m_pSolidObjectsGrid->addObject(pNpc);

        std::shared_ptr<Obstacle> pNpcCollider = std::make_shared<Obstacle>(
            "obstacle",
            o->FloatAttribute("x"), o->FloatAttribute("y"),
            o->IntAttribute("width"), o->IntAttribute("height") / 2
        );
        level.m_pSolidObjectsGrid->addObject(pNpcCollider);
    }
}
