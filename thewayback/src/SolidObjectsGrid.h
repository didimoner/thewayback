#pragma once
#include <SDL_rect.h>

class Collidable;

class SolidObjectsGrid {

private:
    std::vector<std::vector<std::shared_ptr<Collidable>>> m_objects;
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    uint8_t m_gridCols = 0;
    uint8_t m_gridRows = 0;

public:
    SolidObjectsGrid(uint32_t width, uint32_t height, uint8_t gridCols, uint8_t gridRows);

    void addObject(const std::shared_ptr<Collidable>& pObject);
    std::set<std::shared_ptr<Collidable>> getObjectsNearby(const SDL_FRect& collider) const;

private:
    uint32_t calculateIndex(float_t x, float_t y) const;
};
