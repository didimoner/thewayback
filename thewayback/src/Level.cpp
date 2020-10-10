#include "pch.h"
#include "Level.h"
#include "Player.h"
#include "SolidObjectsGrid.h"
#include "SolidObject.h"
#include "DrawableLayer.h"

void Level::update() {
    for (const auto& entry : m_drawableLayers) {
        entry.second->update();
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
