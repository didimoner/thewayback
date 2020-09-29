#pragma once
#include <SDL.h>

class GameStateMachine;
class GameState;
class Log;

class Game {

private:
	Game() {}
	static std::unique_ptr<Game> s_pInstance;
	static Log Logger;

	SDL_Window* m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;
	GameStateMachine* m_pGameStateMachine = nullptr;

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
	
	bool init(const char* title, int x, int y, int width, int height, int flags, 
		GameStateMachine* pGameStateMachine, GameState* pInitialState);
	void update();
	void render();
	void handleEvents();
	void clean();
	void quit();

	bool isRunning() const;
	uint16_t getWindowWidth() const;
	uint16_t getWindowHeight() const;

	SDL_Renderer* getRenderer() const;
	GameState* const getCurrentState() const;

};