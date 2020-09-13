#include "pch.h"
#include "Level.h"
#include "TileLayer.h"
#include "Player.h"

Level::~Level() {
}

void Level::update() {
    // TODO: check collisions

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
