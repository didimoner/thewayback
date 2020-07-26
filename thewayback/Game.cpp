#include "Game.h"
#include <iostream>

bool Game::init(const char* title, int x, int y, int width, int height, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	_pWindow = SDL_CreateWindow(title, x, y, width, height, flags);
	if (_pWindow == 0) {
		return false;
	}

	_pRenderer = SDL_CreateRenderer(_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_pRenderer == 0) {
		return false;
	}

	_running = true;

	return true;
}

void Game::render() {
	SDL_SetRenderDrawColor(_pRenderer, 128, 0, 15, 255);
	SDL_RenderClear(_pRenderer);
	SDL_RenderPresent(_pRenderer);
}

void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				_running = false;
				break;

			default:
				break;
		}
	}
}

void Game::clean() {
	SDL_DestroyWindow(_pWindow);
	SDL_DestroyRenderer(_pRenderer);
	SDL_Quit();
}