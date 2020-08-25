#include "pch.h"
#include "TextureManager.h"
#include <SDL_image.h>
#include "SystemUtils.h"
#include "Log.h"

TextureManager* TextureManager::s_pInstance = nullptr;
Log* TextureManager::Logger = new Log(typeid(TextureManager).name());

TextureManager::~TextureManager() {
    for (auto const& entry : m_textureMap) {
        SDL_DestroyTexture(entry.second);
    }

    m_textureMap.clear();
}

bool TextureManager::load(std::string filename, std::string id, SDL_Renderer* pRenderer) {
    Logger->debug("Loading texture: " + filename);

    std::string resourcesPath = getResourcePath("images");
    std::string filepath = resourcesPath + filename;
    SDL_Surface* pSurface = IMG_Load(filepath.c_str());

    if (pSurface == 0) {
        Logger->error("Cannot load surface from image: " + filepath);
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    
    SDL_FreeSurface(pSurface);

    if (pTexture == 0) {
        Logger->error("Cannot load texture from surface: " + filepath);
        return false;
    }

    m_textureMap[id] = pTexture;
    return true;
}

void TextureManager::draw(std::string textureId, float x, float y, int width, int height,
        SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = m_textureMap[textureId];
    if (pTexture == nullptr) {
        Logger->warn("Texture not found in the map: " + textureId);
    }

    SDL_Rect sourceRect;
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = width;
    sourceRect.h = height;

    SDL_Rect destRect;
    destRect.x = (int) x;
    destRect.y = (int) y;
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopyEx(pRenderer, pTexture, &sourceRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string textureId, float x, float y, int width, int height,
        unsigned currentRow, unsigned currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = m_textureMap[textureId];
    if (pTexture == nullptr) {
        Logger->warn("Texture not found in the map: " + textureId);
    }

    SDL_Rect sourceRect;
    sourceRect.x = width * currentFrame;
    sourceRect.y = height * currentRow;
    sourceRect.w = width;
    sourceRect.h = height;

    SDL_Rect destRect;
    destRect.x = (int) x;
    destRect.y = (int) y;
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopyEx(pRenderer, pTexture, &sourceRect, &destRect, 0, 0, flip);
}

//void TextureManager::drawTile(std::string textureId, float x, float y, int width, int height,
//        unsigned tileId, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
//    SDL_Texture* pTexture = m_textureMap[textureId];
//    if (pTexture == nullptr) {
//        Logger->warn("Texture not found in the map: " + textureId);
//    }
//
//    SDL_Rect sourceRect;
//    sourceRect.x = width * currentFrame;
//    sourceRect.y = height * (currentRow - 1);
//    sourceRect.w = width;
//    sourceRect.h = height;
//
//    SDL_Rect destRect;
//    destRect.x = (int) x;
//    destRect.y = (int) y;
//    destRect.w = width;
//    destRect.h = height;
//
//    SDL_RenderCopyEx(pRenderer, pTexture, &sourceRect, &destRect, 0, 0, flip);
//}
