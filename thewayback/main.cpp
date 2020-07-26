#include <iostream>
#include "Game.h"

int main(int, char**) {
	Game* pGame = new Game();
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
		pGame->handleEvents();
		pGame->update();
		pGame->render();
	}

	pGame->clean();
	return 0;
}