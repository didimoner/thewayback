#pragma once
#include <SDL.h>

class Log;

class TextureManager {

private:
    TextureManager();

    static std::unique_ptr<TextureManager> s_pInstance;
    static Log Logger;

    std::map<std::string, SDL_Texture*> m_textures;

public:
    ~TextureManager();
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    static TextureManager& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new TextureManager());
        }

        return *s_pInstance;
    }

    // ---------------------

    bool load(const std::string& filename, std::string id, SDL_Renderer* pRenderer);

    void draw(const std::string& textureId, float x, float y, int width, int height,
              SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(const std::string& textureId, float x, float y, int width, int height,
                   uint32_t currentRow, uint32_t currentFrame,
                   SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

};
