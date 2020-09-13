#pragma once
#include "pch.h"
#include <SDL_rect.h>
#include "Collidable.h"

enum class ECollisionType;

class Collision {

private:
    static const int offset = 4;

public:
    static void checkCollidables(ECollisionType type, Collidable* pFirst, Collidable* pSecond) {
        for (SDL_Rect firstRect : pFirst->getBoundaries()) {
            for (SDL_Rect secondRect : pSecond->getBoundaries()) {
                if (check(firstRect, secondRect)) {
                    pFirst->onCollide(type, pSecond->getId());
                    pSecond->onCollide(type, pFirst->getId());
                }
            }
        }
    }

private:
    static bool check(SDL_Rect& first, SDL_Rect& second) {
        return ((first.x + first.w - offset >= second.x) && (first.x + offset <= second.x + second.w))
            && ((first.y + first.h - offset >= second.y) && (first.y + offset <= second.y + second.h));
    }

};

