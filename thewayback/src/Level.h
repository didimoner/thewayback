#pragma once
#include "Tileset.h"

class Layer;

class Level {

private:
    friend class LevelParser;
    Level() {}

    unsigned int m_width = 0;
    unsigned int m_height = 0;
    unsigned short m_tileWidth= 0;
    unsigned short m_tileHeight = 0;

    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;

public:
    ~Level();

    std::vector<Tileset>* const getTilesets() {
        return &m_tilesets;
    }
    std::vector<Layer*>* const getLayers() {
        return &m_layers;
    }

    void update();
    void draw();

};

