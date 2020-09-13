#pragma once
#include "pch.h"
#include <SDL_rect.h>

enum class CollisionType;

class Collidable {
    
public:
    virtual SDL_Rect getRect() const = 0;
    virtual void onCollide(CollisionType type, std::string objectId) = 0;

};