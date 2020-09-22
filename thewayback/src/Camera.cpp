#include "pch.h"
#include "Camera.h"

Camera::Camera(const GameObject* pTrackedObject, uint32_t levelWidth, uint32_t levelHeight) {
    m_pTrackedObject = pTrackedObject;
    m_levelWidth = levelWidth;
    m_levelHeight = levelHeight;
}

void Camera::update() {
    if (m_pTrackedObject == nullptr) {
        return;
    }

    uint16_t windowWidth = Game::instance()->getWindowWidth();
    uint16_t windowHeight = Game::instance()->getWindowHeight();

    float x = m_pTrackedObject->getPosition().getX() - (float)(windowWidth - m_pTrackedObject->getWidth()) / 2;
    if (x < 0) {
        x = 0;
    } else if (x + windowWidth > m_levelWidth) {
        x = (float)m_levelWidth - windowWidth;
    }

    float y = m_pTrackedObject->getPosition().getY() - (float)(windowHeight - m_pTrackedObject->getHeight()) / 2;
    if (y < 0) {
        y = 0;
    } else if (y + windowHeight > m_levelHeight) {
        y = (float)m_levelHeight - windowHeight;
    }

    m_position.set(x, y);
}
