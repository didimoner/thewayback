#include "pch.h"
#include "ObstacleLayer.h"
#include "Obstacle.h"
#include "Collision.h"

ObstacleLayer::ObstacleLayer(std::string id, uint32_t width, uint32_t height, uint8_t gridCols, uint8_t gridRows) {
    m_layerId = std::move(id);
    m_width = width;
    m_height = height;
    m_gridCols = gridCols;
    m_gridRows = gridRows;

    for (uint16_t i = 0; i < gridCols * gridRows; i++) {
        m_obstacles.emplace_back();
    }
}

void ObstacleLayer::addObstacle(const std::shared_ptr<Obstacle>& pObstacle) {
    for (uint8_t column = 0; column < m_gridCols; column++) {
        for (uint8_t row = 0; row < m_gridRows; row++) {
            SDL_FRect mapRect;
            mapRect.w = static_cast<float>(m_width) / m_gridRows;
            mapRect.h = static_cast<float>(m_height) / m_gridCols;
            mapRect.x = mapRect.w * row;
            mapRect.y = mapRect.h * column;

            if (Collision::checkRects(pObstacle->getCollider(), mapRect)) {
                const int index = row + m_gridRows * column;
                m_obstacles[index].push_back(pObstacle);
            }
        }
    }
}

std::set<std::shared_ptr<Obstacle>> ObstacleLayer::getObstacles(SDL_FRect boundary) const {
    std::set<uint32_t> indices;
    indices.insert(calculateIndex(boundary.x, boundary.y));
    indices.insert(calculateIndex(boundary.x + boundary.w, boundary.y));
    indices.insert(calculateIndex(boundary.x + boundary.w, boundary.y + boundary.h));
    indices.insert(calculateIndex(boundary.x, boundary.y + boundary.h));

    std::set<std::shared_ptr<Obstacle>> result;
    for (uint32_t index : indices) {
        if (index > m_obstacles.size()) {
            continue;
        }

        auto obstacles = m_obstacles[index];
        result.insert(obstacles.begin(), obstacles.end());
    }

    return result;
}

uint32_t ObstacleLayer::calculateIndex(float x, float y) const {
    const int row = static_cast<int>(x / (static_cast<float>(m_width) / m_gridRows));
    const int column = static_cast<int>(y / (static_cast<float>(m_height) / m_gridCols));
    return row + m_gridRows * column;
}
