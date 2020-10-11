#pragma once
#include "SolidObject.h"
#include "Player.h"
#include "Vector2f.h"

class Portal : public SolidObject {

private:
    std::string m_location;
    Vector2f m_destination;

public:
    Portal(std::string type, float x, float y, uint32_t width, uint32_t height, std::string location, float destX, float destY)
        : SolidObject(std::move(type), x, y, width, height), m_location(std::move(location)), m_destination(destX, destY) {
    }

    void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) override;

};