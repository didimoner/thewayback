#pragma once
#include "pch.h"

class Drawable {

private:
    uint16_t m_priority = 0;

public:
    struct Comparator {
        bool operator()(const Drawable* first, const Drawable* second) const {
            return first->getPriority() < second->getPriority();
        }
    };

public:
    virtual void update() = 0;
    virtual void draw() = 0;

    uint16_t getPriority() const {
        return m_priority;
    }

    void setPriority(uint16_t priority) {
        m_priority = priority;
    }

};
