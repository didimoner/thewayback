#pragma once
#include "Tileset.h"

class Log;

class TileLayer {

private:
    unsigned short m_id = 0;
    std::string m_name;
    const std::vector<Tileset> &m_tilesets;
    std::vector<std::vector<unsigned>> m_tileIds;

    static Log* Logger;
    
public:
    TileLayer(const std::vector<Tileset>& tilesets);
    ~TileLayer() {}

    void update();
    void draw();

    void setId(unsigned short id) {
        this->m_id = id;
    }
    void setName(std::string name) {
        this->m_name = name;
    }
    void setTileIds(const std::vector<std::vector<unsigned>>& data) {
        m_tileIds = data;
    }

private:
    int findTilesetIndex(unsigned tileId) const;

};

