#include "pch.h"
#include "Renderer.h"
#include "Log.h"
#include "Game.h"
#include "TextureManager.h"

std::unique_ptr<Renderer> Renderer::s_pInstance;
Log Renderer::Logger(typeid(Renderer).name());

// TODO: send full

void Renderer::send(const std::string& textureId, SDL_Rect& sourceRect, SDL_Rect& destRect,
        int32_t zIndex, SDL_RendererFlip flip) {
    SDL_Texture* pTexture = TextureManager::instance().getTexture(textureId);
    if (pTexture == nullptr) {
        return;
    }

    send(pTexture, sourceRect, destRect, zIndex, flip);
}

void Renderer::send(SDL_Texture* pTexture, SDL_Rect& sourceRect, SDL_Rect& destRect, 
        int32_t zIndex, SDL_RendererFlip flip) {
    DrawingEntity entity;
    entity.pTexture = pTexture;
    entity.sourceRect = sourceRect;
    entity.destRect = destRect;
    entity.flip = flip;

    m_buffer.emplace(zIndex, entity);
}

void Renderer::flush() {
    for (const auto& entry : m_buffer) {
        DrawingEntity e = entry.second;
        SDL_RenderCopyEx(Game::instance().getRenderer(), e.pTexture, &e.sourceRect, &e.destRect, 0, nullptr, e.flip);
    }

    m_buffer.clear();
}
