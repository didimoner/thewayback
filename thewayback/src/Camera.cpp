#include "pch.h"
#include "Camera.h"

Camera::Camera(uint16_t width, uint16_t height, uint32_t levelWidth, uint32_t levelHeight, 
        const std::shared_ptr<GameObject>& pTrackedObject) {
    m_width = width;
    m_height = height;
    m_levelWidth = levelWidth;
    m_levelHeight = levelHeight;
    if (pTrackedObject) {
        m_pTrackedObject = pTrackedObject;
    }
}

void Camera::update() {
    const auto pTrackedObject = m_pTrackedObject.lock();
    if (!pTrackedObject) {
        return;
    }

    float x;
    float y;

    if (m_levelWidth <= m_width) {
        x = -1 * static_cast<float>(m_width - m_levelWidth) / 2;
    } else {
        x = pTrackedObject->getPosition().getX() - static_cast<float>(m_width - pTrackedObject->getWidth()) / 2;
        if (x < 0) {
            x = 0;
        } else if (x + m_width > m_levelWidth) {
            x = static_cast<float>(m_levelWidth - m_width);
        }
    }

    if (m_levelHeight <= m_height) {
        y = -1 * static_cast<float>(m_height - m_levelHeight) / 2;
    } else {
        y = pTrackedObject->getPosition().getY() - static_cast<float>(m_height - pTrackedObject->getHeight()) / 2;
        if (y < 0) {
            y = 0;
        } else if (y + m_height > m_levelHeight) {
            y = static_cast<float>(m_levelHeight - m_height);
        }
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

void Camera::setLevelSize(uint32_t width, uint32_t height) {
    m_levelWidth = width;
    m_levelHeight = height;
}
