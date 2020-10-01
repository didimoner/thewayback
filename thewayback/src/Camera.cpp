#include "pch.h"
#include "Camera.h"

Camera::Camera(const std::shared_ptr<GameObject>& pTrackedObject, uint16_t width, uint16_t height,
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

    float x = m_pTrackedObject->getPosition().getX() - static_cast<float>(m_width - m_pTrackedObject->getWidth()) / 2;
    if (x < 0) {
        x = 0;
    } else if (x + m_width > m_levelWidth) {
        x = static_cast<float>(m_levelWidth) - m_width;
    }

    float y = m_pTrackedObject->getPosition().getY() - static_cast<float>(m_height - m_pTrackedObject->getHeight()) / 2;
    if (y < 0) {
        y = 0;
    } else if (y + m_height > m_levelHeight) {
        y = static_cast<float>(m_levelHeight) - m_height;
    }

    m_position.set(x, y);
}

Vector2f Camera::getPosition() const {
    return m_position;
}

uint16_t Camera::getWidth() const {
    return m_width;
}

uint16_t Camera::getHeight() const {
    return m_height;
}
