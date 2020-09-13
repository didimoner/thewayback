#pragma once
#include <SDL_rect.h>
#include "Collidable.h"
#include "ECollisionType.h"

class CollidableLayer : public Collidable {

private:
    std::vector<SDL_Rect> m_collidables;
    std::string m_layerId;

public:
    std::vector<SDL_Rect>* const getCollidables() {
        return &m_collidables;
    }
    void setId(std::string id) { 
        m_layerId = id;
    }
    
    std::string getId() const {
        return m_layerId;
    }
    void onCollide(ECollisionType type, std::string objectId);
    std::vector<SDL_Rect> getBoundaries() const;
};

