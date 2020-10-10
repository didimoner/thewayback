#pragma once
#include "pch.h"
#include <SDL_rect.h>

enum class ECollisionType;

class Collidable {

public:
    virtual ~Collidable() = default;

    virtual SDL_FRect getCollider() const = 0;
    virtual void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) = 0;

};
