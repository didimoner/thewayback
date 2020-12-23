#include "pch.h"
#include "TileLayer.h"
#include "Log.h"
#include "Renderer.h"
#include "Game.h"
#include "GameScene.h"
#include "Tileset.h"
#include "Camera.h"
#include "Level.h"

Log TileLayer::Logger(typeid(TileLayer).name());


TileLayer::TileLayer(const std::shared_ptr<Level>& pLevel) {
    m_pLevel = pLevel;
}

void TileLayer::update() {
}

void TileLayer::draw() {
    if (m_globalTileIds.empty()) {
        Logger.warn("Tile data is empty, nothing to draw. Layer: " + m_name);
        return;
    }

    for (uint32_t row = 0; row < m_globalTileIds.size(); row++) {
        for (uint32_t column = 0; column < m_globalTileIds[row].size(); column++) {
            const uint32_t globalTileId = m_globalTileIds[row][column];
            if (globalTileId == 0) {
                continue;
            }

            const auto* pTileset = m_pLevel.lock()->getTilesetByGlobalTileId(globalTileId);
            if (pTileset == nullptr) {
                Logger.warn("There is no tileset for global tile id " + std::to_string(globalTileId));
                continue;
            }

            const auto camera = Game::instance().getActiveScene().lock()->getCamera();
            Vector2f cameraPos = camera.getPosition();
            Vector2f bottomCameraPos(
                cameraPos.getX() + camera.getWidth(),
                cameraPos.getY() + camera.getHeight()
            );
            const int32_t safeOffset = 2;

            const bool topPosCheck = row + safeOffset < cameraPos.getY() / pTileset->tileHeight
                || column + safeOffset < cameraPos.getX() / pTileset->tileWidth;
            const bool botPosCheck = static_cast<int32_t>(row) - safeOffset > bottomCameraPos.getY() / pTileset->tileWidth
                || static_cast<int32_t>(column) - safeOffset > bottomCameraPos.getX() / pTileset->tileHeight;

            if (topPosCheck || botPosCheck) {
                continue;
            }

            const uint32_t localTileId = globalTileId - pTileset->firstGlobalId;
            const float_t x = static_cast<float_t>(column * pTileset->tileWidth);
            const float_t y = static_cast<float_t>(row * pTileset->tileHeight);
            const uint32_t tilesetRow = localTileId / pTileset->columns;
            const uint32_t tilesetColumn = localTileId % pTileset->columns;

            SDL_Rect sourceRect;
            sourceRect.x = pTileset->tileWidth * tilesetColumn;
            sourceRect.y = pTileset->tileHeight * tilesetRow;
            sourceRect.w = pTileset->tileWidth;
            sourceRect.h = pTileset->tileHeight;

            SDL_Rect destRect;
            destRect.x = static_cast<int>(x - cameraPos.getX());
            destRect.y = static_cast<int>(y - cameraPos.getY());
            destRect.w = pTileset->tileWidth;
            destRect.h = pTileset->tileHeight;

            Renderer::instance().send(pTileset->name, sourceRect, destRect, m_zIndex);
        }
    }
}

void TileLayer::setName(std::string name) {
    this->m_name = std::move(name);
}

void TileLayer::setTileIds(const std::vector<std::vector<uint32_t>>& data) {
    m_globalTileIds = data;
}