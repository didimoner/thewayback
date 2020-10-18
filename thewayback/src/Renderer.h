#pragma once
#include <SDL_render.h>

class Log;

class Renderer {

private:
    struct DrawingEntity {
        SDL_Texture* pTexture;
        SDL_Rect sourceRect;
        SDL_Rect destRect;
        double_t angle = 0;
        SDL_Point center;
        SDL_RendererFlip flip;
    };

private:
    Renderer() = default;

    static std::unique_ptr<Renderer> s_pInstance;
    static Log Logger;

    std::multimap<int32_t, DrawingEntity> m_buffer;

public:
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    static Renderer& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new Renderer());
        }

        return *s_pInstance;
    }

    // ---------------------

    void send(const std::string& textureId, SDL_Rect& sourceRect, SDL_Rect& destRect, 
        int32_t zIndex, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void send(SDL_Texture* pTexture, SDL_Rect& sourceRect, SDL_Rect& destRect,
        int32_t zIndex, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void flush();

};