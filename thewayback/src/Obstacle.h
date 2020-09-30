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
        : m_position(x, y), m_width(width), m_height(height) {
    }

    void onCollide(ECollisionType type, std::string objectId) override {
    }

    SDL_FRect getCollider() const override {
        return {m_position.getX(), m_position.getY(), static_cast<float>(m_width), static_cast<float>(m_height)};
    }

};
