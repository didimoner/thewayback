#include "pch.h"
#include "StateParser.h"
#include "SystemUtils.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "Log.h"
#include "Animation.h"

using namespace tinyxml2;

Log StateParser::Logger(typeid(StateParser).name());

bool StateParser::parse(std::string filename, std::string stateId, std::vector<GameObject*>& gameObjects) {
    Logger.debug("Loading state " + stateId + " from " + filename);

    std::string resourcesPath = getResourcePath("data");
    std::string filepath = resourcesPath + filename;

    XMLDocument xmlDoc;

    XMLError loadResult = xmlDoc.LoadFile(filepath.c_str());
    if (loadResult != XML_SUCCESS) {
        Logger.error("Cannot load " + filename);
        return false;
    }

    XMLNode* pRoot = xmlDoc.FirstChildElement();
    if (pRoot == nullptr) {
        Logger.warn("No root element found in " + filename);
        return false;
    }

    XMLElement* pStateElement = pRoot->FirstChildElement(stateId.c_str());
    if (pStateElement == nullptr) {
        Logger.warn("No " + stateId + " element found in " + filename);
        return false;
    }

    XMLElement* pTexturesElement = pStateElement->FirstChildElement("TEXTURES");
    if (pTexturesElement == nullptr) {
        Logger.warn("No TEXTURES element found in " + stateId + " in " + filename);
        return false;
    }
    parseTextures(pTexturesElement);

    XMLElement* pObjectsElement = pStateElement->FirstChildElement("OBJECTS");
    if (pObjectsElement == nullptr) {
        Logger.warn("No OBJECTS element found in " + stateId + " in " + filename);
        return false;
    }
    parseObjects(pObjectsElement, gameObjects);

    return true;
}

void StateParser::parseTextures(XMLElement* pTexturesRoot) {
    for (XMLElement* e = pTexturesRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        std::string filename = e->Attribute("filename");
        std::string id = e->Attribute("id");

        TextureManager::instance().load(filename, id, Game::instance().getRenderer());
    }
}

// TODO: refactor
void StateParser::parseObjects(XMLElement* pObjectsRoot, std::vector<GameObject*>& gameObjects) {
    for (XMLElement* e = pObjectsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        const std::string type = e->Attribute("type");
        const std::string textureId = e->Attribute("textureId");

        const int x = e->IntAttribute("x");
        const int y = e->IntAttribute("y");
        const int width = e->IntAttribute("width");
        const int height = e->IntAttribute("height");
        const uint8_t frames = e->IntAttribute("frames");

        Animation* drawable = dynamic_cast<Animation*>(GameObjectFactory::instance().create(type));
        AnimationInitParams animationInitParams;
        animationInitParams.totalFrames = frames;
        animationInitParams.speed = 4;
        animationInitParams.type = EAnimationType::BOUNCE;
        drawable->init(static_cast<float>(x), static_cast<float>(y), width, height, textureId, animationInitParams);

        gameObjects.push_back(drawable);
    }
}
