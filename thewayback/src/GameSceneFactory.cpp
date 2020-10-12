#include "pch.h"
#include "GameSceneFactory.h"
#include "Log.h"

std::unique_ptr<GameSceneFactory> GameSceneFactory::s_pInstance;
Log GameSceneFactory::Logger(typeid(GameSceneFactory).name());


void GameSceneFactory::registerType(const std::string& type, std::unique_ptr<GameSceneCreator> pCreator) {
    Logger.debug("Registering game scene type " + type);
    if (m_creators.find(type) != m_creators.end()) {
        return;
    }

    m_creators.emplace(type, std::move(pCreator));
}

std::unique_ptr<GameScene> GameSceneFactory::create(const std::string& type) {
    Logger.debug("Creating game scene of type " + type);
    if (m_creators.find(type) == m_creators.end()) {
        Logger.warn("Game scene creator for type " + type + " doesn't exist.");
        return nullptr;
    }

    return m_creators[type]->create();
}
