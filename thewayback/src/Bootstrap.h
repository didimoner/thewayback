#pragma once
#include <SDL.h>
#include "GameObjectFactory.h"
#include "GameSceneFactory.h"
#include "Config.h"
#include "Game.h"
#include "Log.h"
#include "PlayScene.h"

const int FPS = 60;
const int DELAY_TIME = static_cast<int>(1000.0f / FPS);


class Bootstrap {

public:
    static void startGame(const char* title, int x, int y, int width, int height, int flags) {
        loadConfigs();
        registerTypes();

        const auto config = Config::instance().get("system");
        const std::string initialSceneId = config.Get("Initialization", "state", "play_state.xml");
        const bool initialized = Game::instance().init(title, x, y, width, height, flags, initialSceneId);

        if (!initialized) {
            Log::getLogger().error("Game initialization failed");
            return;
        }

        while (Game::instance().isRunning()) {
            const uint32_t frameStart = SDL_GetTicks();

            Game::instance().handleEvents();
            Game::instance().update();
            Game::instance().render();

            const uint32_t frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < DELAY_TIME) {
                SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
            }
        }

        Game::instance().clean();
    }

private:
    static void loadConfigs() {
        Config::instance().load("system.ini", "system");
    }

    static void registerTypes() {
        // game scene types
        GameSceneFactory::instance().registerType("play", std::make_unique<PlaySceneCreator>());

        // game object types
        GameObjectFactory::instance().registerType("player", std::make_unique<PlayerCreator>());
    }

};
