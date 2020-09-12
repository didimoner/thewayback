#include "pch.h"
#include "Level.h"
#include "TileLayer.h"

Level::~Level() {
}

void Level::update() {
    for (TileLayer* pLayer : m_tileLayers) {
        pLayer->update();
    }
}

void Level::draw() {
    for (TileLayer* pLayer : m_tileLayers) {
        pLayer->draw();
    }
}
