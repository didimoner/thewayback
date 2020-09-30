#pragma once
#include "pch.h"
#include <SDL_rect.h>
#include "Collidable.h"

enum class ECollisionType;

class Collision {

private:
    static const int DEFAULT_OFFSET = 4;

public:
    static void checkCollidables(ECollisionType type, Collidable* pFirst, Collidable* pSecond) {
        if (checkRects(pFirst->getBoundary(), pSecond->getBoundary(), DEFAULT_OFFSET)) {
            pFirst->onCollide(type, pSecond->getObjectId());
            pSecond->onCollide(type, pFirst->getObjectId());
        }
    }

    static bool checkRects(const SDL_Rect& first, const SDL_Rect& second, int offset = 0) {
        SDL_FRect firstFRect = {(float)first.x, (float)first.y, (float)first.w, (float)first.h};
        SDL_FRect secondFRect = {(float)second.x, (float)second.y, (float)second.w, (float)second.h};
        return checkRects(firstFRect, secondFRect);
    }

    static bool checkRects(const SDL_FRect& first, const SDL_FRect& second, int offset = 0) {
        return ((first.x + first.w - offset >= second.x) && (first.x + offset <= second.x + second.w))
            && ((first.y + first.h - offset >= second.y) && (first.y + offset <= second.y + second.h));
    }

};
