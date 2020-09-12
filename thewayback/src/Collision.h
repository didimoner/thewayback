#pragma once
#include "pch.h"
#include <SDL_rect.h>
#include "SDLGameObject.h"

class Collision {

public:
    bool check(SDL_Rect& rectA, SDL_Rect& rectB) const {
        return ((rectA.x + rectA.w >= rectB.x) && (rectA.x <= rectB.x + rectB.w))
            && ((rectA.y + rectA.h >= rectB.y) && (rectA.y <= rectB.y + rectB.h));
    }

};

