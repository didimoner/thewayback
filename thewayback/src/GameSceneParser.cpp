#include "pch.h"
#include "GameSceneParser.h"
#include "SystemUtils.h"
#include "LevelParser.h"
#include "XmlHelper.h"
#include "Log.h"
#include "GameScene.h"
#include "PlayScene.h"
#include "GameSceneFactory.h"

using namespace tinyxml2;

Log GameSceneParser::Logger(typeid(GameSceneParser).name());

std::unique_ptr<GameScene> GameSceneParser::parse(const std::string& filename) {
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
    parseObjects(pRoot, *pGameScene);

    return pGameScene;
}

void GameSceneParser::parseObjects(XMLElement* pObjectsRoot, GameScene& gameScene) {
    for (XMLElement* o = pObjectsRoot->FirstChildElement(); o != nullptr; o = o->NextSiblingElement()) {
        std::string objectType = o->Attribute("type");
        std::shared_ptr<Drawable> pGameObject;
        if (objectType == "level") {
            pGameObject = LevelParser::parse(o->Attribute("filename"));
        } else if (objectType == "player") {
            pGameObject = XmlHelper::parseGameObject(o);
        }

        gameScene.m_drawables.emplace(objectType, std::move(pGameObject));
    }
}
