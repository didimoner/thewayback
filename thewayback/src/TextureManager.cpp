#include "pch.h"
#include "TextureManager.h"
#include "SystemUtils.h"
#include <SDL_image.h>

TextureManager* TextureManager::s_pTextureManager = nullptr;

bool TextureManager::load(std::string filename, std::string id, SDL_Renderer* pRenderer) {
    std::string resourcesPath = SystemUtils::getResourcePath("images");
    const char* filepath = (resourcesPath.append(filename)).c_str();
    SDL_Surface* pSurface = IMG_Load(filepath);

    std::cout << filepath << std::endl;

    if (pSurface == 0) {
        std::cout << "surface error" << std::endl;
        // todo: log error
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    
    SDL_FreeSurface(pSurface);

    if (pTexture == 0) {
        std::cout << "texture error" << std::endl;
        // todo: log error
        return false;
    }

    m_textureMap[id] = pTexture;
    return true;
}

void TextureManager::draw(std::string textureId, SDL_Rect rect, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    TextureManager::draw(textureId, rect.x, rect.y, rect.w, rect.h, pRenderer, flip);
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

void TextureManager::drawFrame(std::string textureId, SDL_Rect rect, int currentRow, int currentFrame, 
        SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    TextureManager::drawFrame(textureId, rect.x, rect.y, rect.w, rect.h, currentRow, currentFrame, pRenderer, flip);
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
