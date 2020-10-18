#pragma once
#include <SDL_render.h>

class Log;

class Renderer {

private:
    struct DrawingEntity {
        std::string textureId;
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

    void send(const std::string& textureId, float_t x, float_t y, int32_t width, int32_t height, int32_t zIndex,
              uint32_t row = 0, uint32_t frame = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void flush();

};