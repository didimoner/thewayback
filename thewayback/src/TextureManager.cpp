#include "pch.h"
#include "TextureManager.h"
#include "SystemUtils.h"
#include <SDL_image.h>

TextureManager* TextureManager::s_pTextureManager = nullptr;

bool TextureManager::load(std::string filename, std::string id, SDL_Renderer* pRenderer) {
    std::string resourcesPath = SystemUtils::getResourcePath("images");
    const char* filepath = (resourcesPath + filename).c_str();
    SDL_Surface* pSurface = IMG_Load(filepath);

    if (pSurface == 0) {
        // todo: log error
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    
    SDL_FreeSurface(pSurface);

    if (pTexture == 0) {
        // todo: log error
        return false;
    }

    m_textureMap[id] = pTexture;
    return true;
}

void TextureManager::draw(std::string textureId, int x, int y, int width, int height, 
        SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = m_textureMap[textureId];
    
    // todo: check if a texture exists

    SDL_Rect sourceRect;
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = width;
    sourceRect.h = height;

    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopyEx(pRenderer, pTexture, &sourceRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string textureId, int x, int y, int width, int height, 
        int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = m_textureMap[textureId];

    // todo: check if a texture exists

    SDL_Rect sourceRect;
    sourceRect.x = width * currentFrame;
    sourceRect.y = height * (currentRow - 1);
    sourceRect.w = width;
    sourceRect.h = height;

    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopyEx(pRenderer, pTexture, &sourceRect, &destRect, 0, 0, flip);

}
