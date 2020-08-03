#pragma once

#include <SDL.h>

class Game {

public:

	Game() {}
	~Game() {}

	bool init(const char* title, int x, int y, int width, int height, int flags);
	void render();
	void update() {}
	void handleEvents();
	void clean();

	bool isRunning() {
		return _running;
	}


private:

	SDL_Window* _pWindow = nullptr;
	SDL_Renderer* _pRenderer = nullptr;

	SDL_Texture* _pTexture = nullptr;
	SDL_Rect _sourceRect;
	SDL_Rect _destinationRect;

	bool _running = false;

};