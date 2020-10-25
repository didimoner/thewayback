#include "pch.h"
#include "Level.h"
#include "SolidObjectsGrid.h"
#include "SolidObject.h"
#include "TileLayer.h"

void Level::update() {
    for (const auto& pLayer : m_map) {
        pLayer->update();
    }
    for (const auto& pNpc: m_npcs) {
        pNpc->update();
    }
}

void Level::draw() {
    for (const auto& pLayer : m_map) {
        pLayer->draw();
    }
    for (const auto& pNpc : m_npcs) {
        pNpc->draw();
    }
}

std::string Level::getId() const {
    return m_id;
}

uint32_t Level::getWidthPx() const {
    return m_width * m_tileWidth;
}

uint32_t Level::getHeightPx() const {
    return m_height * m_tileHeight;
}

std::set<std::shared_ptr<SolidObject>> Level::getObjectsNearby(const SDL_FRect& collider) const {
    return m_pSolidObjectsGrid->getObjectsNearby(collider);
}


const Tileset* Level::getTilesetByGlobalTileId(uint32_t globalTileId) {
    for (auto& tileset : m_tilesets) {
        if (globalTileId < tileset.firstGlobalId + tileset.tileCount) {
            return &tileset;
        }
    }

    return nullptr;
}
