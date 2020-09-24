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

    std::vector<Tileset>* const getTilesets();
    std::vector<TileLayer*>* const getTileLayers();
    std::vector<ObstacleLayer*>* const getObstacleLayers();

    uint32_t getWidthPx() const;
    uint32_t getHeightPx() const;
    const Player* getPlayer() const;

    void update();
    void draw();

};

