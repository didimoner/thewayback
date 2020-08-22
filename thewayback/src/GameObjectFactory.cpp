#include "pch.h"
#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::s_pInstance = nullptr;
Log* GameObjectFactory::Logger = new Log(typeid(GameObjectFactory).name());

void GameObjectFactory::registerType(std::string type, GameObjectCreator* pCreator) {
    Logger->debug("Registering object type " + type);

    auto it = m_creators.find(type);
    if (it != m_creators.end()) {
        delete pCreator;
        return;
    }

    m_creators[type] = pCreator;
}

GameObject* GameObjectFactory::create(std::string type) {
    Logger->debug("Creating game object of type " + type);

    GameObjectCreator* pCreator = m_creators[type];
    if (pCreator == nullptr) {
        Logger->warn("Object creator for type " + type + " doesn't exist.");
        return nullptr;
    }

    return pCreator->create();
}
