#pragma once

#include <SDL.h>
#include "GameObject.h"
#include "Log.h"
#include "GameStateMachine.h"

class Game {

private:
	Game() {}
	static Game* s_pInstance;

	SDL_Window* m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;
	Log* m_pLogger = nullptr;
	GameStateMachine* m_pGameStateMachine = nullptr;

	bool m_running = false;

public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	static Game* instance() {
		if (s_pInstance == nullptr) {
			s_pInstance = new Game();
		}
		return s_pInstance;
	}

	// --------------------
	
	bool init(const char* title, int x, int y, int width, int height, int flags);
	void update();
	void render();
	void handleEvents();
	void clean();
	void quit();

	bool isRunning() const;
	SDL_Renderer* getRenderer() const;
	Log* getLogger() const;

};