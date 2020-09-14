#pragma once
#include "pch.h"
#include <SDL_rect.h>
#include "Collidable.h"

enum class ECollisionType;

class Collision {

private:
    static const int offset = 0;

public:
    static void checkCollidables(ECollisionType type, Collidable* pFirst, Collidable* pSecond) {
        if (checkFRects(pFirst->getBoundary(), pSecond->getBoundary())) {
            pFirst->onCollide(type, pSecond->getObjectId());
            pSecond->onCollide(type, pFirst->getObjectId());
        }
    }

    static bool checkRects(const SDL_Rect& first, const SDL_Rect& second) {
        return checkFRects(
            { (float)first.x, (float)first.y, (float)first.w, (float)first.h },
            { (float)second.x, (float)second.y, (float)second.w, (float)second.h }
        );
    }

    static bool checkFRects(const SDL_FRect& first, const SDL_FRect& second) {
        return ((first.x + first.w - offset >= second.x) && (first.x + offset <= second.x + second.w))
            && ((first.y + first.h - offset >= second.y) && (first.y + offset <= second.y + second.h));
    }

};

