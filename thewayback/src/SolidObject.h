#pragma once
#include "Collidable.h"
#include "Vector2f.h"
#include <SDL_rect.h>

class SolidObject : public Collidable {

private:
    std::string m_type;
    Vector2f m_position;
    int m_width = 0;
    int m_height = 0;

public:
    SolidObject(std::string type, float x, float y, uint32_t width, uint32_t height)
        : m_type(std::move(type)), m_position(x, y), m_width(width), m_height(height) {
    }

    std::string getType() const {
        return m_type;
    }

    void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) override {
    }

    SDL_FRect getCollider() const override {
        return {m_position.getX(), m_position.getY(), static_cast<float>(m_width), static_cast<float>(m_height)};
    }

};
