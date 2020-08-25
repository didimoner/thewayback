#pragma once
#include "pch.h"

struct Tileset {
    unsigned int tileCount;
    unsigned int columns;
    unsigned short firstGlobalId;
    unsigned short tileWidth;
    unsigned short tileHeight;
    std::string name;
};