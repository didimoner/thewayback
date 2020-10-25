#pragma once
#include "pch.h"
#include "Vector2f.h"

class Entity {

protected:
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    Vector2f m_position;

public:
    Vector2f getPosition() const {
        return m_position;
    }
    void setPosition(Vector2f position) {
        m_position = position;
    }
    void setPosition(float_t x, float_t y) {
        m_position.set(x, y);
    }

    int32_t getWidth() const {
        return m_width;
    }

    int32_t getHeight() const {
        return m_height;
    }

};