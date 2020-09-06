#include "pch.h"
#include "FontManager.h"
#include "Log.h"
#include "SystemUtils.h"

FontManager* FontManager::s_pInstance = nullptr;
Log* FontManager::Logger = new Log(typeid(FontManager).name());

FontManager::FontManager() {
    if (TTF_Init() != 0) {
        Logger->error("SDL_ttf initialisation error: " + std::string(TTF_GetError()));
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

bool FontManager::loadFont(std::string filename, std::string id, int size) {
    Logger->debug("Loading font: " + filename);

    std::string resourcesPath = getResourcePath("fonts");
    std::string filepath = resourcesPath + filename;
    TTF_Font* pFont = TTF_OpenFont(filepath.c_str(), size);

    if (pFont == nullptr) {
        Logger->error("Cannot load surface from image: " + filepath);
        return false;
    }

    m_fonts[id] = pFont;
    return true;
}

void FontManager::createTexture(std::string fontId, std::string textureId, 
        std::string text, SDL_Color color, SDL_Renderer* pRenderer) {
    Logger->debug("Creating texture " + textureId + " from font " + fontId);
    TTF_Font* pFont = m_fonts[fontId];
    if (pFont == nullptr) {
        Logger->warn("Font not found in the map: " + fontId);
        return;
    }

    SDL_Surface* pSurface = TTF_RenderText_Blended(pFont, text.c_str(), color);
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    SDL_FreeSurface(pSurface);

    m_textures[textureId] = pTexture;
}

void FontManager::createMultilineTexture(std::string fontId, std::string textureId,
    std::string text, unsigned lineWidth, SDL_Color color, SDL_Renderer* pRenderer) {
    Logger->debug("Creating multiline texture " + textureId + " from font " + fontId 
        + " with line width " +std::to_string(lineWidth));
    TTF_Font* pFont = m_fonts[fontId];
    if (pFont == nullptr) {
        Logger->warn("Font not found in the map: " + fontId);
        return;
    }

    SDL_Surface* pSurface = TTF_RenderText_Blended_Wrapped(pFont, text.c_str(), color, lineWidth);
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    SDL_FreeSurface(pSurface);

    m_textures[textureId] = pTexture;
}

void FontManager::removeTexture(std::string textureId) {
    SDL_Texture* pTexture = m_textures[textureId];
    if (pTexture == nullptr) {
        Logger->warn("Texture to remove not found in the map: " + textureId);
        return;
    }

    SDL_DestroyTexture(pTexture);
    m_textures.erase(textureId);
}

void FontManager::draw(std::string textureId, float x, float y, 
        SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = m_textures[textureId];
    if (pTexture == nullptr) {
        Logger->warn("Texture not found in the map: " + textureId);
        return;
    }

    int width = 0;
    int height = 0;
    SDL_QueryTexture(pTexture, NULL, NULL, &width, &height);

    draw(textureId, x, y, width, height, pRenderer, flip);
}

void FontManager::draw(std::string textureId, float x, float y, int width, int height,
        SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = m_textures[textureId];
    if (pTexture == nullptr) {
        Logger->warn("Texture not found in the map: " + textureId);
        return;
    }

    SDL_Rect destRect;
    destRect.x = (int) x;
    destRect.y = (int) y;
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopyEx(pRenderer, pTexture, NULL, &destRect, 0, 0, flip);
}

