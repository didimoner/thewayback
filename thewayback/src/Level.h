#pragma once
#include "Tileset.h"

class Layer;

class Level {

private:
    friend class LevelParser;
    Level() {}

    unsigned int width = 0;
    unsigned int height = 0;
    unsigned short tileWidth= 0;
    unsigned short tileHeight = 0;

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

