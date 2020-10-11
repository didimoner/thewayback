#pragma once
#include "pch.h"

class Drawable {

protected:
    int m_zIndex = 1;

public:
    virtual ~Drawable() = default;

public:
    virtual void update() = 0;
    virtual void draw() = 0;

    void setZIndex(int zIndex) {
        m_zIndex = zIndex;
    }

};
