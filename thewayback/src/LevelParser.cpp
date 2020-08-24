#include "pch.h"
#include <zlib.h>
#include "base64.h"
#include "LevelParser.h"
#include "SystemUtils.h"
#include "TextureManager.h"
#include "Game.h"
#include "Level.h"
#include "Tileset.h"
#include "Log.h"
#include "TileLayer.h"

Log* LevelParser::Logger = new Log(typeid(LevelParser).name());

Level* LevelParser::parse(std::string filename) {
    Logger->debug("Loading level from " + filename);
    
    std::string resourcesPath = getResourcePath("maps");
    std::string filepath = resourcesPath + filename;

    XMLDocument xmlDoc(true, COLLAPSE_WHITESPACE);

    XMLError loadResult = xmlDoc.LoadFile(filepath.c_str());
    if (loadResult != XML_SUCCESS) {
        Logger->error("Cannot load " + filename);
        return nullptr;
    }

    XMLElement* pRoot = xmlDoc.FirstChildElement();
    if (pRoot == nullptr) {
        Logger->warn("No root element found in " + filename);
        return nullptr;
    }

    Level* pLevel = new Level();
    pLevel->m_width = pRoot->IntAttribute("width");
    pLevel->m_height = pRoot->IntAttribute("height");
    pLevel->m_tileWidth = pRoot->IntAttribute("tilewidth");
    pLevel->m_tileHeight = pRoot->IntAttribute("tileheight");

    parseTilesets(pRoot, pLevel->getTilesets());
    parseLayer(pRoot, pLevel);

    return pLevel;
}

void LevelParser::parseTilesets(XMLElement* pTilesetsRoot, std::vector<Tileset>* pTilesets) {
    for (XMLElement* e = pTilesetsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("tileset")) {
            continue;
        }

        Tileset tileset;
        tileset.firstGridId = e->IntAttribute("firstgid");
        tileset.tileWidth = e->IntAttribute("tilewidth");
        tileset.tileHeight = e->IntAttribute("tileheight");
        tileset.tileCount = e->IntAttribute("tilecount");
        tileset.columns = e->IntAttribute("columns");
        tileset.name = e->Attribute("name");
        pTilesets->push_back(tileset);

        XMLElement* pImageElement = e->FirstChildElement("image");
        std::string filename = splitString(pImageElement->Attribute("source"), '/').back();
        TextureManager::instance()->load(filename, tileset.name, Game::instance()->getRenderer());
    }
}

void LevelParser::parseLayer(XMLElement* pLayerRoot, Level* pLevel) {
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
        std::vector<unsigned> uncompressedTileIds(allTilesSize);

        int uncompressStatus = uncompress((Bytef*)&uncompressedTileIds[0], &allTilesSize, 
            (const Bytef*)decodedData.c_str(), decodedData.size());
        if (uncompressStatus != Z_OK) {
            Logger->warn("Something wrong with zlib uncpompression. Code: " + uncompressStatus);
        }

        std::vector<std::vector<unsigned>> tileIds;
        for (unsigned i = 0; i < pLevel->m_height; i++) {
            tileIds.push_back(std::vector<unsigned>(pLevel->m_width));
        }

        for (unsigned row = 0; row < pLevel->m_height; row++) {
            for (unsigned column = 0; column < pLevel->m_width; column++) {
                tileIds[row][column] = uncompressedTileIds[row * pLevel->m_width + column];
            }
        }

        TileLayer* pTileLayer = new TileLayer(*pLevel->getTilesets());
        pTileLayer->setId(e->IntAttribute("id"));
        pTileLayer->setName(e->Attribute("name"));
        pTileLayer->setTileIds(tileIds);

        pLevel->getLayers()->push_back(pTileLayer);
    }
}
