#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Log;

class FontManager {

private:
    FontManager();
    ~FontManager();

    static FontManager* s_pInstance;
    static Log* Logger;

    std::map<std::string, TTF_Font*> m_fonts;
    std::map<std::string, SDL_Texture*> m_textures;

public:
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    static FontManager* instance() {
        if (s_pInstance == nullptr) {
            s_pInstance = new FontManager();
        }

        return s_pInstance;
    }

    // ---------------------

    bool loadFont(std::string filename, std::string id, int size);

    void createTexture(std::string fontId, std::string textureId, 
        std::string text, SDL_Color color, SDL_Renderer* pRenderer);
    void createMultilineTexture(std::string fontId, std::string textureId,
        std::string text, unsigned lineWidth, SDL_Color color, SDL_Renderer* pRenderer);

    void removeTexture(std::string textureId);

    void draw(std::string textureId, float x, float y, 
        SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void draw(std::string textureId, float x, float y, int width, int height,
        SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

};

