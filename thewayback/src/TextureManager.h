#pragma once

#include <SDL.h>
#include "Log.h"

class TextureManager {

private:
	TextureManager() {}

	static TextureManager* s_pInstance;
	static Log* Logger;

	std::map<std::string, SDL_Texture*> m_textureMap;

public:
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	static TextureManager* instance() {
		if (s_pInstance == nullptr) {
			s_pInstance = new TextureManager();
		}

		return s_pInstance;
	}

	// ---------------------

	bool load(std::string filename, std::string id, SDL_Renderer* pRenderer);

	void draw(std::string textureId, SDL_Rect rect, SDL_Renderer* pRenderer,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(std::string textureId, int x, int y, int width, int height, 
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string textureId, SDL_Rect rect, int currentRow, int currentFrame,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string textureId, int x, int y, int width, int height, 
		int currentRow, int currentFrame,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

};