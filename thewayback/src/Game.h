#pragma once
#include <SDL.h>
#include "SceneManager.h"

class GameScene;
class Log;

class Game {

private:
    Game() {
    }

    static std::unique_ptr<Game> s_pInstance;
    static Log Logger;

    SDL_Window* m_pWindow = nullptr;
    SDL_Renderer* m_pRenderer = nullptr;
    std::unique_ptr<SceneManager> m_pSceneManager;

    bool m_running = false;
    uint16_t m_windowWidth = 0;
    uint16_t m_windowHeight = 0;

public:
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static Game& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new Game());
        }
        return *s_pInstance;
    }

    // --------------------

    bool init(const std::string& title, int32_t x, int32_t y, int32_t width, int32_t height, int32_t flags,
              const std::string& initialSceneId);
    void update();
    void render();
    void handleEvents();
    void quit();

    bool isRunning() const;
    uint16_t getWindowWidth() const;
    uint16_t getWindowHeight() const;

    SDL_Renderer* getRenderer() const;
    GameScene& getActiveScene() const;

private:
    bool initSDL(const std::string& title, int32_t x, int32_t y, int32_t width, int32_t height, int32_t flags);

};
