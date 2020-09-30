#pragma once
#include "pch.h"

struct Tileset {
    uint32_t tileCount;
    uint32_t columns;
    uint16_t firstGlobalId;
    uint16_t tileWidth;
    uint16_t tileHeight;
    std::string name;
};
