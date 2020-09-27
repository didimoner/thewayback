#include "pch.h"
#include "Level.h"
#include "TileLayer.h"
#include "Player.h"
#include "ObstacleLayer.h"
#include "Collision.h"
#include "ECollisionType.h"
#include "Obstacle.h"

Level::~Level() {
    delete m_pPlayer;

    for (Drawable* pDrawable: m_drawables) {
        delete pDrawable;
    }
    m_drawables.clear();

    for (ObstacleLayer* pCollidableLayer : m_obstacleLayers) {
        delete pCollidableLayer;
    }
    m_obstacleLayers.clear();
}

void Level::update() {
    for (Drawable* pDrawable : m_drawables) {
        pDrawable->update();
    }

    Vector2f playetPosition = m_pPlayer->getPosition();
    for (ObstacleLayer* pObstacleLayer : m_obstacleLayers) {
        std::set<Obstacle*> obstacles = pObstacleLayer->getObstacles(m_pPlayer->getBoundary());
        for (Obstacle* pObstacle : obstacles) {
            Collision::checkCollidables(ECollisionType::PLAYER_OBSTACLE, m_pPlayer, pObstacle);
        }
    }
}

void Level::draw() {
    for (Drawable* pDrawable: m_drawables) {
        pDrawable->draw();
    }
}

std::vector<Tileset>* const Level::getTilesets() {
    return &m_tilesets;
}

std::multiset<Drawable*, Drawable::Comparator>* const Level::getDrawables() {
    return &m_drawables;
}

std::vector<ObstacleLayer*>* const Level::getObstacleLayers() {
    return &m_obstacleLayers;
}

uint32_t Level::getWidthPx() const {
    return m_width * m_tileWidth;
}

uint32_t Level::getHeightPx() const {
    return m_height * m_tileHeight;
}

const Player* Level::getPlayer() const {
    return m_pPlayer;
}