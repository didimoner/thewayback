#include "pch.h"
#include "Level.h"
#include "TileLayer.h"
#include "Player.h"
#include "ObstacleLayer.h"
#include "Collision.h"
#include "ECollisionType.h"
#include "Obstacle.h"

void Level::update() {
    for (const auto& pDrawable : m_drawables) {
        pDrawable->update();
    }

    for (const auto& pObstacleLayer : m_obstacleLayers) {
        auto obstacles = pObstacleLayer->getObstacles(m_pPlayer->getCollider());
        for (const auto& pObstacle : obstacles) {
            Collision::checkCollidables(ECollisionType::PLAYER_OBSTACLE, *m_pPlayer, *pObstacle);
        }
    }
}

void Level::draw() {
    for (const auto& pDrawable : m_drawables) {
        pDrawable->draw();
    }
}

std::vector<Tileset>& Level::getTilesets() {
    return m_tilesets;
}

std::multiset<std::shared_ptr<Drawable>, Drawable::DrawableComparator>& Level::getDrawables() {
    return m_drawables;
}

std::vector<std::unique_ptr<ObstacleLayer>>& Level::getObstacleLayers() {
    return m_obstacleLayers;
}

uint32_t Level::getWidthPx() const {
    return m_width * m_tileWidth;
}

uint32_t Level::getHeightPx() const {
    return m_height * m_tileHeight;
}

std::shared_ptr<Player>& Level::getPlayer() {
    return m_pPlayer;
}

const Tileset* Level::getTilesetByGlobalTileId(uint32_t globalTileId) {
    for (auto& tileset : m_tilesets) {
        if (globalTileId < tileset.firstGlobalId + tileset.tileCount) {
            return &tileset;
        }
    }

    return nullptr;
}