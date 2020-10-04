#include "pch.h"
#include "GameStateParser.h"
#include "SystemUtils.h"
#include "LevelParser.h"
#include "XmlHelper.h"
#include "Log.h"
#include "GameState.h"
#include "PlayState.h"
#include "GameStateFactory.h"

using namespace tinyxml2;

Log GameStateParser::Logger(typeid(GameStateParser).name());

std::unique_ptr<GameState> GameStateParser::parse(const std::string& filename) {
    Logger.debug("Loading state from " + filename);

    std::string resourcesPath = getResourcePath("states");
    std::string filepath = resourcesPath + filename;

    XMLDocument xmlDoc;
    XMLError loadResult = xmlDoc.LoadFile(filepath.c_str());
    if (loadResult != XML_SUCCESS) {
        Logger.error("Cannot load " + filename);
        return std::unique_ptr<GameState>();
    }

    XMLElement* pRoot = xmlDoc.FirstChildElement();
    if (pRoot == nullptr) {
        Logger.warn("No root element found in " + filename);
        return std::unique_ptr<GameState>();
    }

    auto pGameState = GameStateFactory::instance().create(pRoot->Attribute("type"));
    XMLElement* pObjectsElement = pRoot->FirstChildElement("gameobjects");
    parseObjects(pObjectsElement, *pGameState);

    XMLElement* pLevelElement = pRoot->FirstChildElement("level");
    auto pLevel = LevelParser::parse(pLevelElement->Attribute("filename"));
    pGameState->m_drawables.push_back(pLevel);

    return pGameState;
}

void GameStateParser::parseObjects(XMLElement* pObjectsRoot, GameState& gameState) {
    for (XMLElement* o = pObjectsRoot->FirstChildElement(); o != nullptr; o = o->NextSiblingElement()) {
        auto pGameObject = XmlHelper::parseGameObject(o);
        gameState.m_drawables.push_back(pGameObject);
    }
}
