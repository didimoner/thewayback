#include "pch.h"
#include "TextureManager.h"
#include <SDL_image.h>
#include "SystemUtils.h"
#include "Log.h"

std::unique_ptr<TextureManager> TextureManager::s_pInstance;
Log TextureManager::Logger(typeid(TextureManager).name());

TextureManager::TextureManager() {
    const int initFlags = IMG_INIT_PNG | IMG_INIT_JPG;
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

auto TextureManager::load(const std::string& filename, std::string id, SDL_Renderer* pRenderer) -> bool {
    Logger.debug("Loading texture: " + filename);

    const std::string resourcesPath = getResourcePath("images");
    const std::string filepath = resourcesPath + filename;
    SDL_Surface* pSurface = IMG_Load(filepath.c_str());

    if (pSurface == nullptr) {
        Logger.error("Cannot load surface from image: " + filepath);
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);

    SDL_FreeSurface(pSurface);

    if (pTexture == nullptr) {
        Logger.error("Cannot load texture from surface: " + filepath);
        return false;
    }

    m_textures[id] = pTexture;
    return true;
}

void TextureManager::draw(const std::string& textureId, float x, float y, int width, int height,
                          SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = m_textures[textureId];
    if (pTexture == nullptr) {
        Logger.warn("Texture not found in the map: " + textureId);
        return;
    }

    SDL_Rect sourceRect;
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = width;
    sourceRect.h = height;

    SDL_Rect destRect;
    destRect.x = static_cast<int>(x);
    destRect.y = static_cast<int>(y);
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopyEx(pRenderer, pTexture, &sourceRect, &destRect, 0, nullptr, flip);
}

void TextureManager::drawFrame(const std::string& textureId, float x, float y, int width, int height,
                               uint32_t currentRow, uint32_t currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = m_textures[textureId];
    if (pTexture == nullptr) {
        Logger.warn("Texture not found in the map: " + textureId);
        return;
    }

    SDL_Rect sourceRect;
    sourceRect.x = width * currentFrame;
    sourceRect.y = height * currentRow;
    sourceRect.w = width;
    sourceRect.h = height;

    SDL_Rect destRect;
    destRect.x = static_cast<int>(x);
    destRect.y = static_cast<int>(y);
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopyEx(pRenderer, pTexture, &sourceRect, &destRect, 0, nullptr, flip);
}
