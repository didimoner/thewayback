#include "pch.h"
#include "GameObjectFactory.h"
#include "Log.h"
#include "GameObjectCreator.h"

 GameObjectFactory GameObjectFactory::s_instance;
Log GameObjectFactory::Logger(typeid(GameObjectFactory).name());

GameObjectFactory::~GameObjectFactory() {
    m_creators.clear();
}

void GameObjectFactory::registerType(std::string type, GameObjectCreator* pCreator) {
    Logger.debug("Registering object type " + type);
    if (m_creators.find(type) != m_creators.end()) {
        delete pCreator;
        return;
    }

    m_creators[type] = std::unique_ptr<GameObjectCreator>(pCreator);
}

GameObject* GameObjectFactory::create(std::string type) {
    Logger.debug("Creating game object of type " + type);
    if (m_creators.find(type) == m_creators.end()) {
        Logger.warn("Object creator for type " + type + " doesn't exist.");
        return nullptr;
    }

    return m_creators[type]->create();
}
