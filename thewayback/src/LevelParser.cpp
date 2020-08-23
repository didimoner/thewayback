#include "pch.h"
#include "LevelParser.h"
#include "SystemUtils.h"
#include "TextureManager.h"
#include "Game.h"
#include "Level.h"
#include "Tileset.h"
#include "Log.h"

Log* LevelParser::Logger = new Log(typeid(LevelParser).name());

Level* LevelParser::parse(std::string filename) {
    Logger->debug("Loading level from " + filename);
    
    std::string resourcesPath = getResourcePath("maps");
    std::string filepath = resourcesPath + filename;

    XMLDocument xmlDoc;

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
    pLevel->width = pRoot->IntAttribute("width");
    pLevel->height = pRoot->IntAttribute("height");
    pLevel->tileWidth = pRoot->IntAttribute("tilewidth");
    pLevel->tileHeight = pRoot->IntAttribute("tileheight");

    parseTilesets(pRoot, pLevel->getTilesets());

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

void LevelParser::parseLayer(XMLElement* pLayerRoot) {
}
