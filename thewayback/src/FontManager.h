#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Log;

class FontManager {

private:
    FontManager();

    static std::unique_ptr<FontManager> s_pInstance;
    static Log Logger;

    std::unordered_map<std::string, TTF_Font*> m_fonts;
    std::unordered_map<std::string, SDL_Texture*> m_textures;

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

    bool loadFont(const std::string& filename, std::string id, int32_t size);
    TTF_Font* getFont(const std::string& fontId);

};
