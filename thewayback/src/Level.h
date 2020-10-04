#pragma once
#include "Tileset.h"
#include "Drawable.h"

class DrawableLayer;
class TileLayer;
class ObstacleLayer;
class Player;

class Level : public Drawable {

private:
    friend class LevelParser;
    Level() = default;

    uint32_t m_width = 0;
    uint32_t m_height = 0;
    uint16_t m_tileWidth = 0;
    uint16_t m_tileHeight = 0;
    std::weak_ptr<Player> m_pPlayer;

    std::vector<Tileset> m_tilesets;
    std::map<int16_t, std::shared_ptr<DrawableLayer>> m_drawableLayers;
    std::vector<std::unique_ptr<ObstacleLayer>> m_obstacleLayers;

public:
    void setPlayer(const std::shared_ptr<Player>& pPlayer);

    uint32_t getWidthPx() const;
    uint32_t getHeightPx() const;
    const Tileset* getTilesetByGlobalTileId(uint32_t globalTileId);

    void update() override;
    void draw() override;

};
