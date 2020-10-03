#pragma once
#include "Vector2f.h"
#include "GameObject.h"

class Camera {

private:
    Vector2f m_position;
    uint16_t m_width = 0;
    uint16_t m_height = 0;
    uint32_t m_levelWidth = 0;
    uint32_t m_levelHeight = 0;
    std::weak_ptr<GameObject> m_pTrackedObject;

public:
    Camera(const std::shared_ptr<GameObject>& pTrackedObject, uint16_t width, uint16_t height,
           uint32_t levelWidth, uint32_t levelHeight);

    void update();
    Vector2f getPosition() const;
    uint16_t getWidth() const;
    uint16_t getHeight() const;

};
