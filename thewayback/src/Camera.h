#pragma once
#include "Vector2f.h"

class Camera {

private:
    Vector2f m_position;
    Vector2f m_velocity;

public:
    Vector2f getPosition() const;
    void setPosition(float x, float y);
    void update();
};

