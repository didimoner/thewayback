#include "pch.h"
#include "Camera.h"

Camera::Camera(const GameObject* pTrackedObject, uint16_t width, uint16_t height,
               uint32_t levelWidth, uint32_t levelHeight) {
    m_pTrackedObject = pTrackedObject;
    m_width = width;
    m_height = height;
    m_levelWidth = levelWidth;
    m_levelHeight = levelHeight;
}

void Camera::update() {
    if (m_pTrackedObject == nullptr) {
        return;
    }

    float x = m_pTrackedObject->getPosition().getX() - (float)(m_width - m_pTrackedObject->getWidth()) / 2;
    if (x < 0) {
        x = 0;
    } else if (x + m_width > m_levelWidth) {
        x = (float)m_levelWidth - m_width;
    }

    float y = m_pTrackedObject->getPosition().getY() - (float)(m_height - m_pTrackedObject->getHeight()) / 2;
    if (y < 0) {
        y = 0;
    } else if (y + m_height > m_levelHeight) {
        y = (float)m_levelHeight - m_height;
    }

    m_position.set(x, y);
}
