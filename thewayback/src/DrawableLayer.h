#pragma once
#include "pch.h"
#include "Drawable.h"

class DrawableLayer : public Drawable {

protected:
    int16_t m_zIndex = 0;

public:
    void setZIndex(int zIndex) {
        m_zIndex = zIndex;
    }
};