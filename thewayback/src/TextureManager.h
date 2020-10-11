#pragma once
#include <SDL.h>

class Log;

class TextureManager {

private:
    TextureManager();

    static std::unique_ptr<TextureManager> s_pInstance;
    static Log Logger;

    std::unordered_map<std::string, SDL_Texture*> m_textures;

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

    bool load(const std::string& filename, std::string id);
    SDL_Texture* getTexture(std::string id);

};
