#pragma once
#include "Tileset.h"
#include "Drawable.h"
#include "SolidObjectsGrid.h"

class DrawableLayer;
class TileLayer;

class Level : public Drawable {

private:
    friend class LevelParser;
    Level() = default;

    std::string m_id;
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    uint16_t m_tileWidth = 0;
    uint16_t m_tileHeight = 0;

    std::vector<Tileset> m_tilesets;
    std::vector<std::shared_ptr<DrawableLayer>> m_drawableLayers;
    std::unique_ptr<SolidObjectsGrid> m_pSolidObjectsGrid;

public:
    std::string getId() const;
    uint32_t getWidthPx() const;
    uint32_t getHeightPx() const;
    std::set<std::shared_ptr<SolidObject>> getObjectsNearby(const SDL_FRect& collider) const;
    const Tileset* getTilesetByGlobalTileId(uint32_t globalTileId);

    void update() override;
    void draw() override;

};
