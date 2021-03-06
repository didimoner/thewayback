#pragma once
#include <SDL.h>
#include "GameObjectFactory.h"
#include "GameSceneFactory.h"
#include "Config.h"
#include "Game.h"
#include "Log.h"
#include "PlayScene.h"
#include "Npc.h"
#include "Player.h"

const int32_t FPS = 60;
const int32_t DELAY_TIME = static_cast<int32_t>(1000.0f / FPS);


class Bootstrap {

public:
    static void startGame() {
        loadConfigs();
        registerTypes();

        const int32_t flags = SDL_WINDOW_SHOWN;
        const auto config = Config::instance().get("system");
        const int32_t x = SDL_WINDOWPOS_CENTERED;
        const int32_t y = SDL_WINDOWPOS_CENTERED;
        const int32_t width = config.GetInteger("Settings", "width", 640);
        const int32_t height = config.GetInteger("Settings", "height", 480);
        const std::string initialSceneId = config.Get("Initialization", "state", "play_state.xml");
        const std::string windowTitle = config.Get("Initialization", "windowTitle", "no title");
        const bool initialized = Game::instance().init(windowTitle, x, y, width, height, flags, initialSceneId);

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
                SDL_Delay(static_cast<int32_t>(DELAY_TIME - frameTime));
            }
        }
    }

private:
    static void loadConfigs() {
        Config::instance().load("system.ini", "system");
        Config::instance().load("game.ini", "game");
    }

    static void registerTypes() {
        // game scene types
        GameSceneFactory::instance().registerType("play", std::make_unique<PlaySceneCreator>());

        // game object types
        GameObjectFactory::instance().registerType("player", std::make_unique<PlayerCreator>());
        GameObjectFactory::instance().registerType("npc", std::make_unique<NpcCreator>());
    }

};
