#pragma once
#include "pch.h"
#include "GameObject.h"

class UIElement : public GameObject {

protected:
    bool m_active = true;

public:
    bool isActive() const {
        return m_active;
    }

};
