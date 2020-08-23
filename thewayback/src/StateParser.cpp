#include "pch.h"
#include "StateParser.h"
#include "SystemUtils.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "Log.h"
#include "GameObject.h"

Log* StateParser::Logger = new Log(typeid(StateParser).name());

bool StateParser::parse(std::string filename, std::string stateId, std::vector<GameObject*>& gameObjects) {
    Logger->debug("Loading state " + stateId + " from " + filename);

    std::string resourcesPath = getResourcePath("data");
    std::string filepath = resourcesPath + filename;

    XMLDocument xmlDoc;

    XMLError loadResult = xmlDoc.LoadFile(filepath.c_str());
    if (loadResult != XML_SUCCESS) {
        Logger->error("Cannot load " + filename);
        return false ;
    }

    XMLNode* pRoot = xmlDoc.FirstChildElement();
    if (pRoot == nullptr) {
        Logger->warn("No root element found in " + filename);
        return false;
    }

    XMLElement* pStateElement = pRoot->FirstChildElement(stateId.c_str());
    if (pStateElement == nullptr) {
        Logger->warn("No state " + stateId + " element found in " + filename);
        return false;
    }

    XMLElement* pTexturesElement = pStateElement->FirstChildElement("TEXTURES");
    if (pTexturesElement == nullptr) {
        Logger->warn("No TEXTURES element found in state " + stateId + " in file " + filename);
        return false;
    }
    parseTextures(pTexturesElement);

    XMLElement* pObjectsElement = pStateElement->FirstChildElement("OBJECTS");
    if (pObjectsElement == nullptr) {
        Logger->warn("No OBJECTS element found in state " + stateId + " in file " + filename);
        return false;
    }
    parseObjects(pObjectsElement, gameObjects);

    return true;
}

void StateParser::parseTextures(XMLElement* pTexturesRoot) {
    for (XMLElement* e = pTexturesRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        std::string filename = e->Attribute("filename");
        std::string id = e->Attribute("id");

        TextureManager::instance()->load(filename, id, Game::instance()->getRenderer());
    }
}

void StateParser::parseObjects(XMLElement* pObjectsRoot, std::vector<GameObject*> &gameObjects) {
    for (XMLElement* e = pObjectsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        std::string type = e->Attribute("type");
        std::string textureId = e->Attribute("textureId");

        int x = e->IntAttribute("x");
        int y = e->IntAttribute("y");
        int width = e->IntAttribute("width");
        int height = e->IntAttribute("height");

        GameObject* object = GameObjectFactory::instance()->create(type);
        object->load((float) x, (float) y, width, height, textureId);

        gameObjects.push_back(object);
    }
}
