#pragma once
#include "pch.h"
#include <SDL_rect.h>
#include "Collidable.h"

enum class ECollisionType;

class Collision {

private:
    static const int DEFAULT_OFFSET = 4;

public:
    static void checkCollidables(ECollisionType type, 
            const std::shared_ptr<Collidable>& pFirst, 
            const std::shared_ptr<Collidable>& pSecond) {
        if (testRects(pFirst->getCollider(), pSecond->getCollider(), DEFAULT_OFFSET)) {
            pFirst->onCollide(type, pSecond);
            pSecond->onCollide(type, pFirst);
        }
    }

    static bool testRects(const SDL_Rect& first, const SDL_Rect& second, int offset = 0) {
        const SDL_FRect firstFRect = {
            static_cast<float>(first.x), static_cast<float>(first.y),
            static_cast<float>(first.w), static_cast<float>(first.h)
        };
        const SDL_FRect secondFRect = {
            static_cast<float>(second.x), static_cast<float>(second.y),
            static_cast<float>(second.w), static_cast<float>(second.h)
        };
        return testRects(firstFRect, secondFRect, offset);
    }

    static bool testRects(const SDL_FRect& first, const SDL_FRect& second, int offset = 0) {
        return ((first.x + first.w - offset >= second.x) && (first.x + offset <= second.x + second.w))
            && ((first.y + first.h - offset >= second.y) && (first.y + offset <= second.y + second.h));
    }

};
