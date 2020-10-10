#pragma once
#include "pch.h"
#include "Vector2f.h"
#include "Drawable.h"

class GameObject : public Drawable {

public:
    struct InitParams {
        float x = 0;
        float y = 0;
        uint32_t width = 0;
        uint32_t height = 0;
    };

protected:
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    Vector2f m_position;
    Vector2f m_velocity;
    Vector2f m_acceleration;

public:
    void init(const InitParams& initParams) {
        m_position = { initParams.x, initParams.y };
        m_width = initParams.width;
        m_height = initParams.height;
    }

    void update() override {
        m_velocity += m_acceleration;
        m_position += m_velocity;
    }

    virtual void clean() = 0;

    Vector2f getPosition() const {
        return m_position;
    }
    void setPosition(Vector2f position) {
        m_position = position;
    }
    void setPosition(float x, float y) {
        m_position.set(x, y);
    }

    int getWidth() const {
        return m_width;
    }

    int getHeight() const {
        return m_height;
    }

};
