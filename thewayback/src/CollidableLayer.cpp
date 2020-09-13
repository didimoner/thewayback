#include "pch.h"
#include "CollidableLayer.h"

void CollidableLayer::onCollide(ECollisionType type, std::string objectId) {
    // do notihng...
}

std::vector<SDL_Rect> CollidableLayer::getBoundaries() const {
    return m_collidables;
}
