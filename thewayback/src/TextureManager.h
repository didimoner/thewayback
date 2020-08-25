#pragma once
#include <SDL.h>

class Log;

class TextureManager {

private:
	TextureManager() {}
	~TextureManager();

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

	void draw(std::string textureId, float x, float y, int width, int height,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string textureId, float x, float y, int width, int height,
		unsigned currentRow, unsigned currentFrame,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//void drawTile(std::string textureId, float x, float y, int width, int height,
	//	unsigned tileId, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

};