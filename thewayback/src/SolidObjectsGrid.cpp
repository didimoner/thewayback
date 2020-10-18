#include "pch.h"
#include "SolidObjectsGrid.h"
#include "SolidObject.h"
#include "Collision.h"

SolidObjectsGrid::SolidObjectsGrid(uint32_t width, uint32_t height, uint8_t gridCols, uint8_t gridRows) {
    m_width = width;
    m_height = height;
    m_gridCols = gridCols;
    m_gridRows = gridRows;

    for (uint16_t i = 0; i < gridCols * gridRows; i++) {
        m_objects.emplace_back();
    }
}

void SolidObjectsGrid::addObject(const std::shared_ptr<SolidObject>& pObject) {
    for (uint8_t column = 0; column < m_gridRows; column++) {
        for (uint8_t row = 0; row < m_gridCols; row++) {
            SDL_FRect mapRect;
            mapRect.w = static_cast<float_t>(m_width) / m_gridCols;
            mapRect.h = static_cast<float_t>(m_height) / m_gridRows;
            mapRect.x = mapRect.w * row;
            mapRect.y = mapRect.h * column;

            if (Collision::testRects(pObject->getCollider(), mapRect)) {
                const int32_t index = row + m_gridCols * column;
                m_objects[index].push_back(pObject);
            }
        }
    }
}

std::set<std::shared_ptr<SolidObject>> SolidObjectsGrid::getObjectsNearby(const SDL_FRect& collider) const {
    std::set<uint32_t> indices;
    indices.insert(calculateIndex(collider.x, collider.y));
    indices.insert(calculateIndex(collider.x + collider.w, collider.y));
    indices.insert(calculateIndex(collider.x + collider.w, collider.y + collider.h));
    indices.insert(calculateIndex(collider.x, collider.y + collider.h));

    std::set<std::shared_ptr<SolidObject>> result;
    for (uint32_t index : indices) {
        if (index >= m_objects.size()) {
            continue;
        }

        auto objects = m_objects[index];
        result.insert(objects.begin(), objects.end());
    }

    return result;
}

uint32_t SolidObjectsGrid::calculateIndex(float_t x, float_t y) const {
    const int32_t row = static_cast<int32_t>(x / (static_cast<float_t>(m_width) / m_gridCols));
    const int32_t column = static_cast<int32_t>(y / (static_cast<float_t>(m_height) / m_gridRows));
    return row + m_gridCols * column;
}
