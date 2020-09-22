#pragma once

#include "Vector2f.h"
#include "GameObject.h"
#include "Game.h"

class Camera {

private:
    Vector2f m_position;
    uint32_t m_levelWidth = 0;
    uint32_t m_levelHeight = 0;
    const GameObject* m_pTrackedObject;

public:
    Camera(const GameObject* pTrackedObject, uint32_t levelWidth, uint32_t levelHeight);

    void update();

    Vector2f getPosition() const {
        return m_position;
    }

};

