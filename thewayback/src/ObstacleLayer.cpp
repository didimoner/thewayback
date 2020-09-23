#include "pch.h"
#include "ObstacleLayer.h"
#include "Obstacle.h"
#include "Collision.h"

ObstacleLayer::ObstacleLayer(std::string id, uint32_t width, uint32_t height, uint8_t gridCols, uint8_t gridRows) {
    m_layerId = id;
    m_width = width;
    m_height = height;
    m_gridCols = gridCols;
    m_gridRows = gridRows;

    for (uint16_t i = 0; i < gridCols * gridRows; i++) {
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
    for (uint8_t column = 0; column < m_gridCols; column++) {
        for (uint8_t row = 0; row < m_gridRows; row++) {
            SDL_FRect mapRect;
            mapRect.w = (float)m_width / m_gridRows;
            mapRect.h = (float)m_height / m_gridCols;
            mapRect.x = mapRect.w * row;
            mapRect.y = mapRect.h * column;

            if (Collision::checkRects(pObstacle->getBoundary(), mapRect)) {
                int index = row + m_gridRows * column;
                m_obstacles[index].push_back(pObstacle);
            }
        }
    }
}

std::set<Obstacle*> ObstacleLayer::getObstacles(SDL_FRect boundary) const {
    std::set<uint32_t> indices;
    indices.insert(calculateIndex(boundary.x, boundary.y));
    indices.insert(calculateIndex(boundary.x + boundary.w, boundary.y));
    indices.insert(calculateIndex(boundary.x + boundary.w, boundary.y + boundary.h));
    indices.insert(calculateIndex(boundary.x, boundary.y + boundary.h));
    
    std::set<Obstacle*> result;
    for (uint32_t index : indices) {
        if (index < 0 || index > m_obstacles.size()) {
            continue;
        }

        std::vector<Obstacle*> obstacles = m_obstacles[index];
        result.insert(obstacles.begin(), obstacles.end());
    }

    return result;
}

uint32_t ObstacleLayer::calculateIndex(float x, float y) const {
    int row = (int)(x / ((float)m_width / m_gridRows));
    int column = (int)(y / ((float)m_height / m_gridCols));
    return row + m_gridRows * column;
}

 