#include "pch.h"
#include "GameSceneParser.h"
#include "FontManager.h"
#include "SystemUtils.h"
#include "LevelParser.h"
#include "XmlHelper.h"
#include "Log.h"
#include "GameScene.h"
#include "GameSceneFactory.h"
#include "SoundManager.h"

using namespace tinyxml2;

Log GameSceneParser::Logger(typeid(GameSceneParser).name());

std::shared_ptr<GameScene> GameSceneParser::parse(const std::string& filename) {
    Logger.debug("Loading scene from " + filename);

    std::string resourcesPath = getResourcePath("scenes");
    std::string filepath = resourcesPath + filename;

    XMLDocument xmlDoc;
    XMLError loadResult = xmlDoc.LoadFile(filepath.c_str());
    if (loadResult != XML_SUCCESS) {
        Logger.error("Cannot load " + filename);
        return std::unique_ptr<GameScene>();
    }

    XMLElement* pRoot = xmlDoc.FirstChildElement();
    if (pRoot == nullptr) {
        Logger.warn("No root element found in " + filename);
        return std::unique_ptr<GameScene>();
    }

    auto pGameScene = GameSceneFactory::instance().create(pRoot->Attribute("type"));
    XMLElement* pObjectsRoot = pRoot->FirstChildElement("objects");
    parseObjects(pObjectsRoot, *pGameScene);

    XMLElement* pSoundsRoot = pRoot->FirstChildElement("sounds");
    parseSounds(pSoundsRoot, *pGameScene);

    XMLElement* pFontsRoot = pRoot->FirstChildElement("fonts");
    parseFonts(pFontsRoot, *pGameScene);

    XMLElement* pPropsRoot = pRoot->FirstChildElement("properties");
    parseProps(pPropsRoot, *pGameScene);

    return pGameScene;
}

void GameSceneParser::parseObjects(XMLElement* pObjectsRoot, GameScene& gameScene) {
    for (auto* o = pObjectsRoot->FirstChildElement(); o != nullptr; o = o->NextSiblingElement()) {
        std::string objectType = o->Attribute("type");
        std::shared_ptr<Drawable> pGameObject;
        if (objectType == "player") {
            pGameObject = XmlHelper::parseGameObject(o);
        }

        gameScene.m_sceneObjects.emplace(objectType, std::move(pGameObject));
    }
}

void GameSceneParser::parseSounds(XMLElement* pSoundsRoot, GameScene& gameScene) {
    for (auto* s = pSoundsRoot->FirstChildElement(); s != nullptr; s = s->NextSiblingElement()) {
        const std::string id = s->Attribute("id");
        const std::string filename = s->Attribute("filename");
        const std::string type = s->Attribute("type");
        if (type == "effect") {
            SoundManager::instance().loadSound(filename, id);
        } else if (type == "music") {
            SoundManager::instance().loadMusic(filename, id);
        }
    }
}

void GameSceneParser::parseFonts(tinyxml2::XMLElement* pFontsRoot, GameScene& gameScene) {
    for (auto* s = pFontsRoot->FirstChildElement(); s != nullptr; s = s->NextSiblingElement()) {
        const std::string id = s->Attribute("id");
        const std::string filename = s->Attribute("filename");
        const auto fontSizes = splitString(s->Attribute("fontSizes"), ',');
        for (std::string fontSize : fontSizes) {
            FontManager::instance().loadFont(filename, id + "_" + fontSize, std::stoi(fontSize));
        }
    }
}

void GameSceneParser::parseProps(tinyxml2::XMLElement* pPropsRoot, GameScene& gameScene) {
    for (auto* p = pPropsRoot->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        gameScene.m_sceneProps.addProperty(p->Attribute("name"), p->Attribute("value"));
    }
}
