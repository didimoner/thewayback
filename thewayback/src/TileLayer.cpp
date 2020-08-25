#include "pch.h"
#include "TileLayer.h"
#include "Log.h"
#include "TextureManager.h"
#include "Game.h"

Log* TileLayer::Logger = new Log(typeid(TileLayer).name());

TileLayer::TileLayer(const std::vector<Tileset>& tilesets) : m_tilesets(tilesets) {
}

void TileLayer::update() {
}

void TileLayer::draw() {
    if (m_tileIds.empty()) {
        Logger->warn("Tile data is empty, nothing to draw. Layer: " + m_name);
        return;
    }
    
    unsigned rows = m_tileIds.size();
    unsigned cols = m_tileIds.back().size();

    for (unsigned row = 0; row < m_tileIds.size(); row++) {
        for (unsigned column = 0; column < m_tileIds[row].size(); column++) {
            unsigned tileId = m_tileIds[row][column];
            if (tileId == 0) {
                continue;
            }

            unsigned tilesetIndex = findTilesetIndex(tileId);
            if (tilesetIndex == -1) {
                Logger->warn("Tile ID out of tilesets' bounds: " + tileId);
                continue;
            }

            Tileset tileset = m_tilesets[tilesetIndex];
            unsigned localTileId = tileId - tileset.firstGlobalId;
            float x = (float) (column * tileset.tileWidth);
            float y = (float) (row * tileset.tileHeight);
            unsigned tilesetRow = localTileId / tileset.columns;
            unsigned tilesetColumn = localTileId % tileset.columns;

            TextureManager::instance()->drawFrame(tileset.name, x, y, tileset.tileWidth, tileset.tileHeight, 
                tilesetRow, tilesetColumn, Game::instance()->getRenderer());
        }
    }
}

unsigned TileLayer::findTilesetIndex(unsigned tileId) const {
    for (unsigned i = 0; i < m_tilesets.size(); i++) {
        if (tileId < m_tilesets[i].firstGlobalId + m_tilesets[i].tileCount) {
            return i;
        }
    }

    return -1;
}