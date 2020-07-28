#ifndef __GAME__
#define __GAME__

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

	SDL_Window* _pWindow = NULL;
	SDL_Renderer* _pRenderer = NULL;

	SDL_Texture* _pTexture = NULL;
	SDL_Rect _sourceRect;
	SDL_Rect _destinationRect;

	bool _running = false;

};

#endif // !__GAME__
