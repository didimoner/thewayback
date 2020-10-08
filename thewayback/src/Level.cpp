#include "pch.h"
#include "Level.h"
#include "Player.h"
#include "ObstacleLayer.h"
#include "Collision.h"
#include "ECollisionType.h"
#include "Obstacle.h"
#include "DrawableLayer.h"

void Level::update() {
    for (const auto& entry : m_drawableLayers) {
        entry.second->update();
    }

    // todo: think about moving this part
    const auto pPlayer = m_pPlayer.lock();
    if (!pPlayer) {
        return;
    }

    // TODO: move to special layer
    pPlayer->update();

    for (const auto& pObstacleLayer : m_obstacleLayers) {
        auto obstacles = pObstacleLayer->getObstacles(pPlayer->getCollider());
        for (const auto& pObstacle : obstacles) {
            Collision::checkCollidables(ECollisionType::PLAYER_OBSTACLE, *pPlayer, *pObstacle);
        }
    }
}

void Level::draw() {
    for (const auto& entry : m_drawableLayers) {
        entry.second->draw();
    }

    // TODO: move to special layer
    m_pPlayer.lock()->draw();
}

void Level::setPlayer(const std::shared_ptr<Player>& pPlayer) {
    m_pPlayer = pPlayer;
}

uint32_t Level::getWidthPx() const {
    return m_width * m_tileWidth;
}

uint32_t Level::getHeightPx() const {
    return m_height * m_tileHeight;
}

const Tileset* Level::getTilesetByGlobalTileId(uint32_t globalTileId) {
    for (auto& tileset : m_tilesets) {
        if (globalTileId < tileset.firstGlobalId + tileset.tileCount) {
            return &tileset;
        }
    }

    return nullptr;
}