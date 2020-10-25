#include "pch.h"
#include "TextureManager.h"
#include <SDL_image.h>
#include "SystemUtils.h"
#include "Log.h"
#include "Game.h"

std::unique_ptr<TextureManager> TextureManager::s_pInstance;
Log TextureManager::Logger(typeid(TextureManager).name());

TextureManager::TextureManager() {
    const int32_t initFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(initFlags) & initFlags) != initFlags) {
        Logger.error("SDL_Image initialization error: " + std::string(IMG_GetError()));
    }
}

TextureManager::~TextureManager() {
    for (auto const& entry : m_textures) {
        SDL_DestroyTexture(entry.second);
    }

    m_textures.clear();
}

bool TextureManager::load(const std::string& filename, const std::string& id) {
    if (m_textures.find(id) != m_textures.end()) {
        return true;
    }

    Logger.debug("Loading texture: " + filename + " with id " + id);

    const std::string resourcesPath = getResourcePath("images");
    const std::string filepath = resourcesPath + filename;
    SDL_Surface* pSurface = IMG_Load(filepath.c_str());

    if (pSurface == nullptr) {
        Logger.error("Cannot load surface from image: " + filepath);
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::instance().getRenderer(), pSurface);
    SDL_FreeSurface(pSurface);

    if (pTexture == nullptr) {
        Logger.error("Cannot load texture from surface: " + filepath);
        return false;
    }

    m_textures[id] = pTexture;
    return true;
}

SDL_Texture* TextureManager::getTexture(const std::string& id) {
    if (m_textures.find(id) == m_textures.end()) {
        Logger.warn("Texture not found in the map: " + id);
        return nullptr;
    }

    return m_textures[id];
}
