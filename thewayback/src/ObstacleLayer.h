#pragma once
#include <SDL_rect.h>

class Obstacle;

class ObstacleLayer {

private:
    std::vector<std::vector<Obstacle*>> m_obstacles;
    std::string m_layerId;
    Uint32 m_width = 0;
    Uint32 m_height = 0;
    Uint8 m_gridCols = 0;
    Uint8 m_gridRows = 0;

public:
    ObstacleLayer(std::string id, Uint32 width, Uint32 height, Uint8 gridCols, Uint8 gridRows);
    ~ObstacleLayer();

    void addObstacle(Obstacle* pObstacle);
    std::set<Obstacle*> getObstacles(SDL_FRect boundary) const;

private:
    Uint32 calculateIndex(float x, float y) const;
};

