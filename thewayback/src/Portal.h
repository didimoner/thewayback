#pragma once
#include "SolidObject.h"
#include "Player.h"
#include "ECollisionType.h"
#include "Vector2f.h"
#include "Game.h"
#include "PlayScene.h"

class Portal : public SolidObject {

private:
    std::string m_location;
    Vector2f m_destination;

public:
    Portal(std::string type, float x, float y, uint32_t width, uint32_t height, std::string location, float destX, float destY)
        : SolidObject(type, x, y, width, height), m_location(std::move(location)), m_destination(destX, destY) {
    }

    void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) override {
        if (type == ECollisionType::PLAYER_PORTAL) {
            const auto pPlayer = std::dynamic_pointer_cast<Player>(pCollidable);
            pPlayer->setPosition(m_destination);

            Game::instance().getActiveScene().onEvent(PlayScene::EventType::CHANGE_LEVEL, m_location);
        }
    }

};