#include "pch.h"
#include "FontManager.h"
#include "Log.h"
#include "SystemUtils.h"
#include "Game.h"

std::unique_ptr<FontManager> FontManager::s_pInstance;
Log FontManager::Logger(typeid(FontManager).name());

FontManager::FontManager() {
    if (TTF_Init() != 0) {
        Logger.error("SDL_ttf initialization error: " + std::string(TTF_GetError()));
    }
}

FontManager::~FontManager() {
    for (auto const& entry : m_fonts) {
        SDL_free(entry.second);
    }
    m_fonts.clear();

    for (auto const& entry : m_textures) {
        SDL_DestroyTexture(entry.second);
    }

    m_textures.clear();
}

bool FontManager::loadFont(const std::string& filename, std::string id, int32_t size) {
    Logger.debug("Loading font: " + filename);

    const std::string resourcesPath = getResourcePath("fonts");
    const std::string filepath = resourcesPath + filename;
    TTF_Font* pFont = TTF_OpenFont(filepath.c_str(), size);

    if (pFont == nullptr) {
        Logger.error("Cannot load surface from image: " + filepath);
        return false;
    }

    m_fonts[id] = pFont;
    return true;
}

void FontManager::createTexture(const std::string& fontId, const std::string& textureId, 
        const std::string& text, SDL_Color color) {
    Logger.debug("Creating texture " + textureId + " from font " + fontId);
    TTF_Font* pFont = m_fonts[fontId];
    if (pFont == nullptr) {
        Logger.warn("Font not found in the map: " + fontId);
        return;
    }

    SDL_Surface* pSurface = TTF_RenderText_Blended(pFont, text.c_str(), color);
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::instance().getRenderer(), pSurface);
    SDL_FreeSurface(pSurface);

    m_textures[textureId] = pTexture;
}

void FontManager::createMultilineTexture(const std::string& fontId, const std::string& textureId,
        const std::string& text, uint32_t lineWidth, SDL_Color color) {
    Logger.debug("Creating multiline texture " + textureId + " from font " + fontId
        + " with line width " + std::to_string(lineWidth));
    TTF_Font* pFont = m_fonts[fontId];
    if (pFont == nullptr) {
        Logger.warn("Font not found in the map: " + fontId);
        return;
    }

    SDL_Surface* pSurface = TTF_RenderText_Blended_Wrapped(pFont, text.c_str(), color, lineWidth);
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::instance().getRenderer(), pSurface);
    SDL_FreeSurface(pSurface);

    m_textures[textureId] = pTexture;
}

void FontManager::removeTexture(const std::string& textureId) {
    SDL_Texture* pTexture = m_textures[textureId];
    if (pTexture == nullptr) {
        Logger.warn("Texture to remove not found in the map: " + textureId);
        return;
    }

    SDL_DestroyTexture(pTexture);
    m_textures.erase(textureId);
}

void FontManager::draw(const std::string& textureId, float_t x, float_t y, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = m_textures[textureId];
    if (pTexture == nullptr) {
        Logger.warn("Texture not found in the map: " + textureId);
        return;
    }

    int32_t width = 0;
    int32_t height = 0;
    SDL_QueryTexture(pTexture, nullptr, nullptr, &width, &height);

    draw(textureId, x, y, width, height, flip);
}

void FontManager::draw(const std::string& textureId, float_t x, float_t y, int32_t width, int32_t height, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = m_textures[textureId];
    if (pTexture == nullptr) {
        Logger.warn("Texture not found in the map: " + textureId);
        return;
    }

    SDL_Rect destRect;
    destRect.x = static_cast<int32_t>(x);
    destRect.y = static_cast<int32_t>(y);
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopyEx(Game::instance().getRenderer(), pTexture, nullptr, &destRect, 0, nullptr, flip);
}
