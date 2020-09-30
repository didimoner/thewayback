#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Log;

class FontManager {

private:
    FontManager();

    static std::unique_ptr<FontManager> s_pInstance;
    static Log Logger;

    std::map<std::string, TTF_Font*> m_fonts;
    std::map<std::string, SDL_Texture*> m_textures;

public:
    ~FontManager();
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    static FontManager& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new FontManager());
        }

        return *s_pInstance;
    }

    // ---------------------

    bool loadFont(const std::string& filename, std::string id, int size);

    void createTexture(const std::string& fontId, const std::string& textureId,
                       const std::string& text, SDL_Color color, SDL_Renderer* pRenderer);
    void createMultilineTexture(const std::string& fontId, const std::string& textureId,
                                const std::string& text, uint32_t lineWidth, SDL_Color color, 
                                SDL_Renderer* pRenderer);

    void removeTexture(const std::string& textureId);

    void draw(const std::string& textureId, float x, float y,
              SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void draw(const std::string& textureId, float x, float y, int width, int height,
              SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

};
