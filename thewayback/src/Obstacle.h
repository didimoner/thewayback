#pragma once
#include "Collidable.h"
#include "Vector2f.h"
#include <SDL_rect.h>
#include "Entity.h"

class Obstacle : public Entity, public Collidable {

public:
    Obstacle(const std::string& type, float_t x, float_t y, uint32_t width, uint32_t height) {
        m_type = type;
        m_position = Vector2f(x, y);
        m_width = width;
        m_height = height;
    }

    void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) override {
    }

    SDL_FRect getCollider() const override {
        return {m_position.getX(), m_position.getY(), static_cast<float_t>(m_width), static_cast<float_t>(m_height)};
    }

};
