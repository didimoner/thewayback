#include "pch.h"
#include "Level.h"
#include "TileLayer.h"
#include "Player.h"
#include "CollidableLayer.h"
#include "Collision.h"
#include "ECollisionType.h"

Level::~Level() {
    delete m_pPlayer;

    for (TileLayer* pTileLayer : m_tileLayers) {
        delete pTileLayer;
    }
    m_tileLayers.clear();

    for (CollidableLayer* pCollidableLayer : m_collidableLayers) {
        delete pCollidableLayer;
    }
    m_collidableLayers.clear();
}

void Level::update() {
    for (TileLayer* pLayer : m_tileLayers) {
        pLayer->update();
    }
    
    m_pPlayer->update();
    
    for (CollidableLayer* pCollidableLayer : m_collidableLayers) {
        Collision::checkCollidables(ECollisionType::PLAYER_OBSTACLE, m_pPlayer, pCollidableLayer);
    }
}

void Level::draw() {
    for (TileLayer* pLayer : m_tileLayers) {
        pLayer->draw();
    }

    m_pPlayer->draw();
}
