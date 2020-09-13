#include "pch.h"
#include <zlib.h>
#include <SDL_rect.h>
#include "base64.h"
#include "LevelParser.h"
#include "SystemUtils.h"
#include "TextureManager.h"
#include "Game.h"
#include "Level.h"
#include "Tileset.h"
#include "Log.h"
#include "TileLayer.h"
#include "CollidableLayer.h"
#include "SDLGameObject.h"
#include "Player.h"
#include "GameObjectFactory.h"

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

        TextureManager::instance()->load(filename, textureId, Game::instance()->getRenderer());
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
        TextureManager::instance()->load(filename, tileset.name, Game::instance()->getRenderer());
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

        pLevel->getTileLayers()->push_back(pTileLayer);
    }
}

void LevelParser::parseObjectLayers(XMLElement* pObjectsRoot, Level* pLevel) {
    for (XMLElement* e = pObjectsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("objectgroup")) {
            continue;
        }

        std::string layerType = getStringProperty(e, "type");
        if (layerType == "collidables") {
            parseCollidables(e, pLevel);
        } else if (layerType == "game_objects") {
            parseGameObjects(e, pLevel);
        }
    }

}

void LevelParser::parseCollidables(XMLElement* pRoot, Level* pLevel) {
    CollidableLayer* pCollidableLayer = new CollidableLayer();
    pCollidableLayer->setId(pRoot->Attribute("name"));

    for (XMLElement* o = pRoot->FirstChildElement("object"); o != nullptr; o = o->NextSiblingElement()) {
        SDL_Rect boundary;
        boundary.x = o->IntAttribute("x");
        boundary.y = o->IntAttribute("y");
        boundary.w = o->IntAttribute("width");
        boundary.h = o->IntAttribute("height");
        pCollidableLayer->getCollidables()->push_back(boundary);
    }

    pLevel->getCollidableLayers()->push_back(pCollidableLayer);
}

void LevelParser::parseGameObjects(XMLElement* pRoot, Level* pLevel) {
    for (XMLElement* o = pRoot->FirstChildElement("object"); o != nullptr; o = o->NextSiblingElement()) {
        int x = o->IntAttribute("x");
        int y = o->IntAttribute("y");
        int width = o->IntAttribute("width");
        int height = o->IntAttribute("height");
        std::string type = o->Attribute("type");
        std::string textureId = getStringProperty(o, "textureId");
        Uint16 frames = getIntProperty(o, "frames");

        SDLGameObject* object = static_cast<SDLGameObject*>(GameObjectFactory::instance()->create(type));
        object->init((float)x, (float)y, width, height, textureId, frames);

        if (type == "player" && pLevel->m_pPlayer == nullptr) {
            pLevel->m_pPlayer = static_cast<Player*>(object);
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

    Logger->warn("There is no property with name " + name);
    return "";
}

int LevelParser::getIntProperty(XMLElement* pElementRoot, std::string name) const {
    XMLElement* pPropsElement = pElementRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        if (p->Attribute("name") == name) {
            return p->IntAttribute("value");
        }
    }

    Logger->warn("There is no property with name " + name);
    return 0;
}
