#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include <SDL_rect.h>

class Obstacle : public Collidable {

private:
    Vector2f m_position;
    int m_width = 0;
    int m_height = 0;

public:
    Obstacle(float x, float y, uint32_t width, uint32_t height) 
        : m_position(x, y), m_width(width), m_height(height) { }

    void onCollide(ECollisionType type, std::string objectId) { }
    SDL_FRect getBoundary() const {
        return { m_position.getX(), m_position.getY(), (float)m_width, (float)m_height };
    }

};
