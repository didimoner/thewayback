#include "pch.h"
#include "Config.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "GameState.h"
#include "Log.h"

std::unique_ptr<Game> Game::s_pInstance;
Log Game::Logger(typeid(Game).name());

Game::~Game() {
	clean();
}

bool Game::init(const char* title, int x, int y, int width, int height, int flags,
		GameStateMachine* pGameStateMachine, GameState* pInitialState) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger.error("SDL_Init Error: " + std::string(SDL_GetError()));
		return false;
	}

	m_pWindow = SDL_CreateWindow(title, x, y, width, height, flags);
	if (m_pWindow == 0) {
		Logger.error("Cannot initialise windows.");
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == 0) {
		Logger.error("Cannot create renderer.");
		return false;
	}

	m_running = true;
	m_windowWidth = width;
	m_windowHeight = height;

	m_pGameStateMachine = pGameStateMachine;
	m_pGameStateMachine->pushState(pInitialState);
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
	InputHandler::instance().update();
}

void Game::quit() {
	m_running = false;
}

void Game::clean() {
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

bool Game::isRunning() const {
	return m_running;
}

uint16_t Game::getWindowWidth() const {
	return m_windowWidth;
}

uint16_t Game::getWindowHeight() const {
	return m_windowHeight;
}

SDL_Renderer* Game::getRenderer() const {
	return m_pRenderer;
}

GameState* const Game::getCurrentState() const {
	return m_pGameStateMachine->getCurrentState();
}
