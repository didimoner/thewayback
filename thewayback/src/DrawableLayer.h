#pragma once
#include "pch.h"
#include "Drawable.h"

class DrawableLayer : public Drawable {

private:
    int16_t m_priority = 0;

public:
    void setPriority(int16_t priority) {
        m_priority = priority;
    }

    int16_t getPriority() const {
        return m_priority;
    }

};