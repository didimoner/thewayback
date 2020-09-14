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

    unsigned int m_width = 0;
    unsigned int m_height = 0;
    unsigned short m_tileWidth= 0;
    unsigned short m_tileHeight = 0;

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

    void update();
    void draw();

};

