#pragma once
#include "pch.h"
#include <SDL_rect.h>

enum class ECollisionType;

class Collidable {
    
public:
    virtual std::string getId() const = 0;
    virtual std::vector<SDL_Rect> getBoundaries() const = 0;
    virtual void onCollide(ECollisionType type, std::string objectId) = 0;

};