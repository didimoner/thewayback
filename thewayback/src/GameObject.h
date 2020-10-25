#pragma once
#include "pch.h"
#include "Vector2f.h"
#include "Drawable.h"
#include "Entity.h"

class GameObject : public Entity, public Drawable {

public:
    struct InitParams {
        float_t x = 0;
        float_t y = 0;
        uint32_t width = 0;
        uint32_t height = 0;
        int32_t zIndex = 1;
    };

protected:
    Vector2f m_velocity;
    Vector2f m_acceleration;

public:
    void init(const InitParams& initParams) {
        m_position = { initParams.x, initParams.y };
        m_width = initParams.width;
        m_height = initParams.height;
        m_zIndex = initParams.zIndex;
    }

    void update() override {
        m_velocity += m_acceleration;
        m_position += m_velocity;
    }

    virtual void clean() = 0;

};
