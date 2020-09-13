#include "pch.h"
#include "Level.h"
#include "TileLayer.h"
#include "Player.h"
#include "CollidableLayer.h"
#include "Collision.h"
#include "ECollisionType.h"

Level::~Level() {
}

void Level::update() {
    for (CollidableLayer* pCollidableLayer : m_collidableLayers) {
        Collision::checkCollidables(ECollisionType::PLAYER_OBSTACLE, m_pPlayer, pCollidableLayer);
    }


    for (TileLayer* pLayer : m_tileLayers) {
        pLayer->update();
    }

    m_pPlayer->update();
}

void Level::draw() {
    for (TileLayer* pLayer : m_tileLayers) {
        pLayer->draw();
    }

    m_pPlayer->draw();
}
