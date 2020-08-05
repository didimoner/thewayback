#include "pch.h"
#include "Game.h"
#include <SDL_image.h>
#include "SystemUtils.h"
#include "Player.h"
#include "TextureManager.h"

Game* Game::s_pInstance = nullptr;

bool Game::init(const char* title, int x, int y, int width, int height, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_pWindow = SDL_CreateWindow(title, x, y, width, height, flags);
	if (m_pWindow == 0) {
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == 0) {
		return false;
	}

	m_pLogger = new Log();

	// -----------------------------------------

	TextureManager::instance()->load("newchar02-2.png", "player", m_pRenderer);

	BaseObject* pPlayer = new Player(25, 50, 32, 32, "player");
	m_gameObjects.push_back(pPlayer);

	// -----------------------------------------

	m_running = true;

	return true;
}

void Game::render() {
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);

	for (BaseObject* object : m_gameObjects) {
		object->draw();
	}

	SDL_RenderPresent(m_pRenderer);
}

void Game::update() {
	for (BaseObject* object : m_gameObjects) {
		object->update();
	}
}

void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_running = false;
				break;

			default:
				break;
		}
	}
}

void Game::clean() {
	for (BaseObject* object : m_gameObjects) {
		object->clean();
	}

	delete m_pLogger;

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}