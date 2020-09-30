#pragma once
#include "GameObjectCreator.h"

class GameObject;
class Log;

class GameObjectFactory {

private:
    GameObjectFactory() {
    }

    static std::unique_ptr<GameObjectFactory> s_pInstance;
    static Log Logger;

    std::map<std::string, std::unique_ptr<GameObjectCreator>> m_creators;

public:
    ~GameObjectFactory();
    GameObjectFactory(const GameObjectFactory&) = delete;
    GameObjectFactory& operator=(const GameObjectFactory&) = delete;

    static GameObjectFactory& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new GameObjectFactory);
        }

        return *s_pInstance;
    }

    // ----------------------------------

    void registerType(std::string type, std::unique_ptr<GameObjectCreator>&& pCreator);
    GameObject* create(std::string type);

};
