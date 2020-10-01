#include "pch.h"
#include "GameObjectFactory.h"
#include "Log.h"
#include "GameObjectCreator.h"

std::unique_ptr<GameObjectFactory> GameObjectFactory::s_pInstance;
Log GameObjectFactory::Logger(typeid(GameObjectFactory).name());

GameObjectFactory::~GameObjectFactory() {
    m_creators.clear();
}

void GameObjectFactory::registerType(const std::string& type, std::unique_ptr<GameObjectCreator> pCreator) {
    Logger.debug("Registering object type " + type);
    if (m_creators.find(type) != m_creators.end()) {
        return;
    }

    m_creators.emplace(type, std::move(pCreator));
}

std::shared_ptr<GameObject> GameObjectFactory::create(const std::string& type) {
    Logger.debug("Creating game object of type " + type);
    if (m_creators.find(type) == m_creators.end()) {
        Logger.warn("Object creator for type " + type + " doesn't exist.");
        return nullptr;
    }

    return m_creators[type]->create();
}
