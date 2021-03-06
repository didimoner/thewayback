#pragma once
#include "GameSceneCreator.h"

class Log;
class GameScene;

class GameSceneFactory {
    
private:
    GameSceneFactory() = default;

    static std::unique_ptr<GameSceneFactory> s_pInstance;
    static Log Logger;

    std::unordered_map<std::string, std::unique_ptr<GameSceneCreator>> m_creators;

public:
    GameSceneFactory(const GameSceneFactory&) = delete;
    GameSceneFactory& operator=(const GameSceneFactory&) = delete;

    static GameSceneFactory& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new GameSceneFactory);
        }

        return *s_pInstance;
    }

    // ----------------------------------

    void registerType(const std::string & type, std::unique_ptr<GameSceneCreator> pCreator);
    std::shared_ptr<GameScene> create(const std::string & type);

};