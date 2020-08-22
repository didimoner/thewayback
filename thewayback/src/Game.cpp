#include "pch.h"
#include "Game.h"
#include <SDL_image.h>
#include "SystemUtils.h"
#include "TextureManager.h"
#include "Config.h"
#include "InputHandler.h"

// todo: move this outside
#include "MenuState.h"
#include "GameObjectFactory.h"
#include "Player.h"

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
	m_pGameStateMachine = new GameStateMachine();

	// -----------------------------------------

	// loading configs
	Config::instance()->load("system.ini", "system");

	// -----------------------------------------

	// TODO: move this outside of engine
	GameObjectFactory::instance()->registerType("player", new PlayerCreator());

	// -----------------------------------------

	m_pGameStateMachine->pushState(new MenuState());

	m_running = true;
	return true;
}

void Game::update() {
	m_pGameStateMachine->update();
}


void Game::render() {
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->draw();

	SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents() {
	InputHandler::instance()->update();
}

void Game::quit() {
	m_running = false;
}

void Game::clean() {
	InputHandler::instance()->clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();

	delete m_pLogger;
}

bool Game::isRunning() const {
	return m_running;
}

SDL_Renderer* Game::getRenderer() const {
	return m_pRenderer;
}

Log* Game::getLogger() const {
	return m_pLogger;
}