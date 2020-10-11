#include "pch.h"
#include "Renderer.h"
#include "Log.h"
#include "Game.h"
#include "TextureManager.h"

std::unique_ptr<Renderer> Renderer::s_pInstance;
Log Renderer::Logger(typeid(Renderer).name());


void Renderer::send(const std::string& textureId, float x, float y, int width, int height, int zIndex,
        uint32_t row, uint32_t frame, SDL_RendererFlip flip) {
    SDL_Rect sourceRect;
    sourceRect.x = width * frame;
    sourceRect.y = height * row;
    sourceRect.w = width;
    sourceRect.h = height;

    SDL_Rect destRect;
    destRect.x = static_cast<int>(x);
    destRect.y = static_cast<int>(y);
    destRect.w = width;
    destRect.h = height;

    DrawingEntity entity;
    entity.textureId = textureId;
    entity.sourceRect = sourceRect;
    entity.destRect = destRect;
    entity.flip = flip;

    m_buffer.emplace(zIndex, entity);
}

void Renderer::flush() {
    for (const auto& entry : m_buffer) {
        DrawingEntity e = entry.second;

        SDL_Texture* pTexture = TextureManager::instance().getTexture(e.textureId);
        if (pTexture == nullptr) {
            Logger.warn("Texture not found in the map: " + e.textureId);
            return;
        }

        SDL_RenderCopyEx(Game::instance().getRenderer(), pTexture, &e.sourceRect, &e.destRect, 0, nullptr, e.flip);
    }

    m_buffer.clear();
}
