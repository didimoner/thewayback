#include "pch.h"
#include "Portal.h"
#include "ECollisionType.h"
#include "Game.h"
#include "PlayScene.h"
#include "SoundPlayer.h"

void Portal::onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) {
    if (type == ECollisionType::PLAYER_PORTAL) {
        const auto pPlayer = std::dynamic_pointer_cast<Player>(pCollidable);
        pPlayer->setPosition(m_destination);
        SoundPlayer::playSound("ding");

        Game::instance().getActiveScene().lock()->onEvent(PlayScene::EventType::CHANGE_LEVEL, m_location);
    }
}