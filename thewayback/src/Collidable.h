#pragma once
#include "pch.h"
#include <SDL_rect.h>

enum class ECollisionType;

class Collidable {

protected:
    std::string m_objectId;

public:
    virtual ~Collidable() = default;

    std::string getObjectId() const {
        return m_objectId;
    }

    void setObjectId(std::string id) {
        m_objectId = std::move(id);
    }

    virtual SDL_FRect getCollider() const = 0;
    virtual void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) = 0;

};
