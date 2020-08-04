#pragma once

#include <SDL.h>

class Game {

public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	static Game* instance() {
		if (s_pInstance == nullptr) {
			s_pInstance = new Game();
		}
		return s_pInstance;
	}
	
	bool init(const char* title, int x, int y, int width, int height, int flags);
	void render();
	void update() {}
	void handleEvents();
	void clean();

	bool isRunning() {
		return m_running;
	}

private:
	Game() {}
	static Game* s_pInstance;

	SDL_Window* m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;

	bool m_running = false;

};