#include "pch.h"
#include "Camera.h"
#include "InputHandler.h"

Vector2f Camera::getPosition() const {
    return m_position;
}

void Camera::setPosition(float x, float y) {
    m_position.set(x, y);
}

void Camera::update() {
	m_position += m_velocity;
}
