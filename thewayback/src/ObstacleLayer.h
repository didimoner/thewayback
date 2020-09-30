#pragma once
#include <SDL_rect.h>

class Obstacle;

class ObstacleLayer {

private:
    std::vector<std::vector<Obstacle*>> m_obstacles;
    std::string m_layerId;
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    uint8_t m_gridCols = 0;
    uint8_t m_gridRows = 0;

public:
    ObstacleLayer(std::string id, uint32_t width, uint32_t height, uint8_t gridCols, uint8_t gridRows);
    ~ObstacleLayer();

    void addObstacle(Obstacle* pObstacle);
    std::set<Obstacle*> getObstacles(SDL_FRect boundary) const;

private:
    uint32_t calculateIndex(float x, float y) const;
};
