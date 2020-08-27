#pragma once
#include "Tileset.h"

class Layer {

protected:
    virtual ~Layer() {}

public:
    virtual void update() = 0;
    virtual void draw() = 0;

};
