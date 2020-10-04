#pragma once
#include "DrawableLayer.h"

class Log;
class Level;

class TileLayer : public DrawableLayer {

private:
    std::string m_name;
    std::weak_ptr<Level> m_pLevel;
    std::vector<std::vector<uint32_t>> m_globalTileIds;

    static Log Logger;

public:
    TileLayer(const std::shared_ptr<Level>& pLevel);

    void update() override;
    void draw() override;

    void setName(std::string name);
    void setTileIds(const std::vector<std::vector<uint32_t>>& data);

};
