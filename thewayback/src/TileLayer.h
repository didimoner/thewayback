#pragma once
#include "Tileset.h"
#include "Drawable.h"

class Log;

class TileLayer : public Drawable {

private:
    std::string m_name;
    const std::vector<Tileset> m_tilesets;
    std::vector<std::vector<uint32_t>> m_tileIds;

    static Log Logger;
    
public:
    TileLayer(const std::vector<Tileset>& tilesets);
    ~TileLayer() {}

    void update();
    void draw();

    void setName(std::string name);
    void setTileIds(const std::vector<std::vector<uint32_t>>& data);

private:
    int findTilesetIndex(uint32_t tileId) const;

};

