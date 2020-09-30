#pragma once
#include "pch.h"
#include <SDL_rect.h>

enum class ECollisionType;

class Collidable {

protected:
    std::string m_objectId;

public:
    std::string getObjectId() const {
        return m_objectId;
    }

    void setObjectId(std::string id) {
        m_objectId = id;
    }

    virtual SDL_FRect getBoundary() const = 0;
    virtual void onCollide(ECollisionType type, std::string objectId) = 0;

};
