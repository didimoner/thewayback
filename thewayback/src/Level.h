#pragma once
#include "Tileset.h"
#include <SDL_rect.h>

class TileLayer;
class ObstacleLayer;
class Player;

class Level {

private:
    friend class LevelParser;
    Level() {}

    uint32_t m_width = 0;
    uint32_t m_height = 0;
    uint16_t m_tileWidth = 0;
    uint16_t m_tileHeight = 0;

    Player* m_pPlayer = nullptr;

    std::vector<Tileset> m_tilesets;
    std::vector<TileLayer*> m_tileLayers;
    std::vector<ObstacleLayer*> m_obstacleLayers;

public:
    ~Level();

    std::vector<Tileset>* const getTilesets() {
        return &m_tilesets;
    }
    std::vector<TileLayer*>* const getTileLayers() {
        return &m_tileLayers;
    }
    std::vector<ObstacleLayer*>* const getObstacleLayers() {
        return &m_obstacleLayers;
    }

    uint32_t getWidthPx() {
        return m_width * m_tileWidth;
    }
    uint32_t getHeightPx() {
        return m_height * m_tileHeight;
    }
    const Player* getPlayer() const {
        return m_pPlayer;
    }

    void update();
    void draw();

};

