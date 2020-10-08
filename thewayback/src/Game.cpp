#include "pch.h"
#include "Game.h"
#include "InputHandler.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "GameSceneParser.h"
#include "Log.h"

std::unique_ptr<Game> Game::s_pInstance;
Log Game::Logger(typeid(Game).name());

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int x, int y, int width, int height, int flags,
        const std::string& initialSceneId) {
    if (!initSDL(title, x, y, width, height, flags)) {
        return false;
    }

    m_running = true;
    m_windowWidth = width;
    m_windowHeight = height;

    auto pInitialScene = GameSceneParser::parse(initialSceneId);
    if (!pInitialScene) {
        Logger.error("Can not load initial scene " + initialSceneId);
        return false;
    }

    m_pGameSceneMachine = std::make_unique<GameSceneManager>();
    m_pGameSceneMachine->push(std::move(pInitialScene));
    return true;
}

void Game::update() {
    m_pGameSceneMachine->update();
}

void Game::render() {
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);

    m_pGameSceneMachine->draw();

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

GameScene& Game::getActiveScene() const {
    return m_pGameSceneMachine->getActiveScene();
}

bool Game::initSDL(const char* title, int x, int y, int width, int height, int flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger.error("SDL_Init Error: " + std::string(SDL_GetError()));
        return false;
    }

    m_pWindow = SDL_CreateWindow(title, x, y, width, height, flags);
    if (m_pWindow == nullptr) {
        Logger.error("Cannot initialise windows.");
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_pRenderer == nullptr) {
        Logger.error("Cannot create renderer.");
        return false;
    }

    return true;
}
