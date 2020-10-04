#pragma once

class Log;
class GameState;
class GameStateCreator;

class GameStateFactory {
    
private:
    GameStateFactory() = default;

    static std::unique_ptr<GameStateFactory> s_pInstance;
    static Log Logger;

    std::unordered_map<std::string, std::unique_ptr<GameStateCreator>> m_creators;

public:
    GameStateFactory(const GameStateFactory&) = delete;
    GameStateFactory& operator=(const GameStateFactory&) = delete;

    static GameStateFactory& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new GameStateFactory);
        }

        return *s_pInstance;
    }

    // ----------------------------------

    void registerType(const std::string & type, std::unique_ptr<GameStateCreator> pCreator);
    std::unique_ptr<GameState> create(const std::string & type);

};