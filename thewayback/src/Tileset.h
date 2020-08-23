#pragma once
#include "pch.h"

struct Tileset {
    unsigned int tileCount;
    unsigned int columns;
    unsigned short firstGridId;
    unsigned short tileWidth;
    unsigned short tileHeight;
    std::string name;
};