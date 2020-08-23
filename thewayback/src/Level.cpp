#include "pch.h"
#include "Level.h"
#include "Layer.h"

Level::~Level() {
}

void Level::update() {
    for (Layer* pLayer : m_layers) {
        pLayer->update();
    }
}

void Level::draw() {
    for (Layer* pLayer : m_layers) {
        pLayer->draw();
    }
}
