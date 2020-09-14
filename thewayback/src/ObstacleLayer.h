#pragma once
#include <SDL_rect.h>
#include "Collidable.h"
#include "ECollisionType.h"
#include "Vector2f.h"

class Obstacle;

class ObstacleLayer {

private:
    std::vector<std::vector<Obstacle*>> m_obstacles;
    std::string m_layerId;
    Uint32 m_width = 0;
    Uint32 m_height = 0;
    Uint8 m_size;

public:
    ObstacleLayer(std::string id, Uint32 width, Uint32 height, Uint8 size);
    ~ObstacleLayer();

    void addObstacle(Obstacle* pObstacle);
    const std::vector<Obstacle*>& getObstacles(float x, float y) const;
};

