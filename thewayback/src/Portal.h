#pragma once
#include "Collidable.h"
#include <SDL_rect.h>
#include "Player.h"
#include "ECollisionType.h"
#include "Vector2f.h"
#include "Game.h"
#include "PlayScene.h"

class Portal : public Collidable {

private:
    Vector2f m_position;
    int m_width = 0;
    int m_height = 0;
    std::string m_location;
    Vector2f m_destination;

public:
    Portal(float x, float y, uint32_t width, uint32_t height, std::string location, float destX, float destY)
        : m_position(x, y), m_width(width), m_height(height), m_location(std::move(location)), m_destination(destX, destY) {
    }

    void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) override {
        if (type == ECollisionType::PLAYER_PORTAL) {
            const auto pPlayer = std::dynamic_pointer_cast<Player>(pCollidable);
            pPlayer->setPosition(m_destination);

            Game::instance().getActiveScene().onEvent(PlayScene::EventType::CHANGE_LEVEL, m_location);
        }
    }

    SDL_FRect getCollider() const override {
        return { m_position.getX(), m_position.getY(), static_cast<float>(m_width), static_cast<float>(m_height) };
    }


};