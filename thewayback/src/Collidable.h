#pragma once
#include "pch.h"
#include <SDL_rect.h>

enum class ECollisionType;

class Collidable {

protected:
    std::string m_type;

public:
    virtual ~Collidable() = default;

    virtual SDL_FRect getCollider() const = 0;
    virtual void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) = 0;

    void setType(const std::string& type) {
        m_type = type;
    }
    std::string getType() const {
        return m_type;
    }
};
