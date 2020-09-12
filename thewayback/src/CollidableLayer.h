#pragma once
#include <SDL_rect.h>

class CollidableLayer {

private:
    std::vector<SDL_Rect> m_collidables;

public:
    std::vector<SDL_Rect>* const getCollidables() {
        return &m_collidables;
    }

};

