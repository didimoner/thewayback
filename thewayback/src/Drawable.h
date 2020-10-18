#pragma once
#include "pch.h"

class Drawable {

protected:
    int32_t m_zIndex = 1;

public:
    virtual ~Drawable() = default;

public:
    virtual void update() = 0;
    virtual void draw() = 0;

    void setZIndex(int32_t zIndex) {
        m_zIndex = zIndex;
    }

};
