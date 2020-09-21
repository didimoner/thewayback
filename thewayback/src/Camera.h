#pragma once
#include "pch.h"
#include "Vector2f.h"

class Camera {

private:
    Vector2f m_position;
    Vector2f m_velocity;

public:
    Vector2f getPosition() const {
        return m_position;
    }
    void setPosition(Vector2f position) {
        m_position = position;
    }
    void setPosition(float x, float y) {
        m_position.set(x, y);
    }

    Vector2f getVelocity() const {
        return m_velocity;
    }
    void setVelocity(float x, float y) {
        m_velocity.set(x, y);
    }

    void update() {
        m_position += m_velocity;
    }
};

