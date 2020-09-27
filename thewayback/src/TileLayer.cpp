#include "pch.h"
#include "TileLayer.h"
#include "Log.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameState.h"
#include "Tileset.h"

std::unique_ptr<Log> TileLayer::Logger = std::make_unique<Log>(typeid(TileLayer).name());

TileLayer::TileLayer(const std::vector<Tileset>& tilesets) : m_tilesets(tilesets) {
}

void TileLayer::update() {
}

void TileLayer::draw() {
    if (m_tileIds.empty()) {
        Logger->warn("Tile data is empty, nothing to draw. Layer: " + m_name);
        return;
    }

    for (uint32_t row = 0; row < m_tileIds.size(); row++) {
        for (uint32_t column = 0; column < m_tileIds[row].size(); column++) {
            uint32_t tileId = m_tileIds[row][column];
            if (tileId == 0) {
                continue;
            }

            int tilesetIndex = findTilesetIndex(tileId);
            if (tilesetIndex == -1) {
                Logger->warn("Tile ID out of tilesets' bounds: " + tileId);
                continue;
            }

            Tileset tileset = m_tilesets[tilesetIndex];
            const Camera* pCamera = Game::instance().getCurrentState()->getCamera();
            Vector2f cameraPos = pCamera->getPosition();
            Vector2f bottomCameraPos(
                cameraPos.getX() + pCamera->getWidth(), 
                cameraPos.getY() + pCamera->getHeight()
            );
            int safeOffset = 2;

            bool topPosCheck = row + safeOffset < cameraPos.getY() / tileset.tileHeight 
                || column + safeOffset < cameraPos.getX() / tileset.tileWidth;
            bool botPosCheck = (int)row - safeOffset > bottomCameraPos.getY() / tileset.tileWidth
                || (int)column - safeOffset > bottomCameraPos.getX() / tileset.tileHeight;

            if (topPosCheck || botPosCheck) {
                continue;
            }

            uint32_t localTileId = tileId - tileset.firstGlobalId;
            float x = (float) (column * tileset.tileWidth);
            float y = (float) (row * tileset.tileHeight);
            uint32_t tilesetRow = localTileId / tileset.columns;
            uint32_t tilesetColumn = localTileId % tileset.columns;

            TextureManager::instance().drawFrame(
                tileset.name, 
                x - cameraPos.getX(), 
                y - cameraPos.getY(), 
                tileset.tileWidth, 
                tileset.tileHeight, 
                tilesetRow, 
                tilesetColumn, 
                Game::instance().getRenderer()
            );
        }
    }
}

void TileLayer::setName(std::string name) {
    this->m_name = name;
}

void TileLayer::setTileIds(const std::vector<std::vector<uint32_t>>& data) {
    m_tileIds = data;
}

int TileLayer::findTilesetIndex(uint32_t tileId) const {
    for (uint32_t i = 0; i < m_tilesets.size(); i++) {
        if (tileId < m_tilesets[i].firstGlobalId + m_tilesets[i].tileCount) {
            return i;
        }
    }

    return -1;
}