#include "pch.h"
#include <SDL.h>
#include "SystemUtils.h"

#include "Game.h"
#include "Log.h"

const int FPS = 60;
const int DELAY_TIME = (int) (1000.0f / FPS);


int main(int, char**) {
	Uint32 frameStart, frameTime;

	Game* pGame = Game::instance();
	bool initialized = pGame->init("Test title",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		SDL_WINDOW_SHOWN
	);

	if (!initialized) {
		std::cout << "Game initialisation failed" << std::endl;
		return 1;
	}

	while (pGame->isRunning()) {
		frameStart = SDL_GetTicks();

		pGame->handleEvents();
		pGame->update();
		pGame->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) {
			SDL_Delay((int) (DELAY_TIME - frameTime));
		}
	}

	pGame->clean();

	return 0;
}