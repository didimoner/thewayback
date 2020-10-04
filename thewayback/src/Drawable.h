#pragma once
#include "pch.h"

class Drawable {

public:
    virtual ~Drawable() = default;

public:
    virtual void update() = 0;
    virtual void draw() = 0;

};
