#include "pch.h"
#include "Bootstrap.h"


int main(int, char**) {
	Bootstrap::startGame("Test title",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1366, 720,
		SDL_WINDOW_SHOWN);

	return 0;
}