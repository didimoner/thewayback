#pragma once
#include "Tileset.h"
#include "Drawable.h"

class TileLayer;
class ObstacleLayer;
class Player;

class Level : Drawable {

private:
    friend class LevelParser;
    Level() = default;

    uint32_t m_width = 0;
    uint32_t m_height = 0;
    uint16_t m_tileWidth = 0;
    uint16_t m_tileHeight = 0;

    Player* m_pPlayer = nullptr;

    std::multiset<Drawable*, Drawable::Comparator> m_drawables;
    std::vector<Tileset> m_tilesets;
    std::vector<ObstacleLayer*> m_obstacleLayers;

public:
    ~Level();

    std::vector<Tileset>* getTilesets();
    std::multiset<Drawable*, Drawable::Comparator>* getDrawables();
    std::vector<ObstacleLayer*>* getObstacleLayers();

    uint32_t getWidthPx() const;
    uint32_t getHeightPx() const;
    const Player* getPlayer() const;

    void update() override;
    void draw() override;

};
