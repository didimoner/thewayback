#pragma once
#include <SDL.h>
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "SplashState.h"
#include "GameObjectFactory.h"
#include "Player.h"
#include "Config.h"
#include "Game.h"
#include "Log.h"

const int FPS = 60;
const int DELAY_TIME = (int)(1000.0f / FPS);


class Bootstrap {

public:
    static void startGame(const char* title, int x, int y, int width, int height, int flags) {
		loadConfigs();
		registerTypes();

		bool initialized = Game::instance().init(title, x, y, width, height, flags,
			new GameStateMachine(), new PlayState());

		if (!initialized) {
			Log::getLogger().error("Game initialisation failed");
			return;
		}

		uint32_t frameStart, frameTime;
		while (Game::instance().isRunning()) {
			frameStart = SDL_GetTicks();

			Game::instance().handleEvents();
			Game::instance().update();
			Game::instance().render();

			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}

		Game::instance().clean();
    }

private:
	static void loadConfigs() {
		Config::instance().load("system.ini", "system");
	}

	static void registerTypes() {
		GameObjectFactory::instance()
			.registerType("player", std::unique_ptr<PlayerCreator>(new PlayerCreator));
	}

};