#pragma once
#include "pch.h"
#include <SDL_rect.h>
#include "Collidable.h"

enum class ECollisionType;

class Collision {

private:
    static const int DEFAULT_OFFSET = 4;

public:
    static void checkCollidables(ECollisionType type, Collidable& first, Collidable& second) {
        if (checkRects(first.getCollider(), second.getCollider(), DEFAULT_OFFSET)) {
            first.onCollide(type, second.getObjectId());
            second.onCollide(type, first.getObjectId());
        }
    }

    static bool checkRects(const SDL_Rect& first, const SDL_Rect& second, int offset = 0) {
        const SDL_FRect firstFRect = {
            static_cast<float>(first.x), static_cast<float>(first.y),
            static_cast<float>(first.w), static_cast<float>(first.h)
        };
        const SDL_FRect secondFRect = {
            static_cast<float>(second.x), static_cast<float>(second.y),
            static_cast<float>(second.w), static_cast<float>(second.h)
        };
        return checkRects(firstFRect, secondFRect, offset);
    }

    static bool checkRects(const SDL_FRect& first, const SDL_FRect& second, int offset = 0) {
        return ((first.x + first.w - offset >= second.x) && (first.x + offset <= second.x + second.w))
            && ((first.y + first.h - offset >= second.y) && (first.y + offset <= second.y + second.h));
    }

};
