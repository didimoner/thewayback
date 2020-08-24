#pragma once
#include "Layer.h"

class TileLayer : public Layer {

private:
    unsigned short id = 0;
    std::string name;

    const std::vector<Tileset> &m_tilesets;
    std::vector<std::vector<unsigned>> m_tileIds;
    
public:
    TileLayer(const std::vector<Tileset>& tilesets);
    ~TileLayer() {}

    void update();
    void draw();

    void setId(unsigned short id) {
        this->id = id;
    }
    void setName(std::string name) {
        this->name = name;
    }
    void setTileIds(const std::vector<std::vector<unsigned>>& data) {
        m_tileIds = data;
    }

};

