#include "pch.h"
#include "GameStateFactory.h"
#include "GameStateCreator.h"
#include "Log.h"

std::unique_ptr<GameStateFactory> GameStateFactory::s_pInstance;
Log GameStateFactory::Logger(typeid(GameStateFactory).name());


void GameStateFactory::registerType(const std::string& type, std::unique_ptr<GameStateCreator> pCreator) {
    Logger.debug("Registering game state type " + type);
    if (m_creators.find(type) != m_creators.end()) {
        return;
    }

    m_creators.emplace(type, std::move(pCreator));
}

std::unique_ptr<GameState> GameStateFactory::create(const std::string& type) {
    Logger.debug("Creating game state of type " + type);
    if (m_creators.find(type) == m_creators.end()) {
        Logger.warn("Game state creator for type " + type + " doesn't exist.");
        return nullptr;
    }

    return m_creators[type]->create();
}
