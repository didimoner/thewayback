#include "pch.h"
#include "ObstacleLayer.h"
#include "Obstacle.h"
#include "Collision.h"

ObstacleLayer::ObstacleLayer(std::string id, Uint32 width, Uint32 height, Uint8 size) {
    m_layerId = id;
    m_width = width;
    m_height = height;
    m_size = size;

    for (Uint16 i = 0; i < size * size; i++) {
        m_obstacles.push_back(std::vector<Obstacle*>());
    }   
}

ObstacleLayer::~ObstacleLayer() {
    for (std::vector<Obstacle*> list : m_obstacles) {
        for (Obstacle* pObstacle : list) {
            delete pObstacle;
        }  
    }
    m_obstacles.clear();
}

void ObstacleLayer::addObstacle(Obstacle* pObstacle) {
    for (Uint8 column = 0; column < m_size; column++) {
        for (Uint8 row = 0; row < m_size; row++) {
            SDL_FRect mapRect;
            mapRect.w = (float)m_width / m_size;
            mapRect.h = (float)m_height / m_size;
            mapRect.x = mapRect.w * row;
            mapRect.y = mapRect.h * column;

            if (Collision::checkFRects(pObstacle->getBoundary(), mapRect)) {
                int index = row + m_size * column;
                m_obstacles[index].push_back(pObstacle);
            }
        }
    }
}

const std::vector<Obstacle*>& ObstacleLayer::getObstacles(float x, float y) const {
    int row = (int)(x / ((float)m_width / m_size));
    int column = (int)(y / ((float)m_height / m_size));

    int index = row + m_size * column;
    return m_obstacles[index];
}

