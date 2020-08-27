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
	InputHandler* pInputHandler = InputHandler::instance();
	if (pInputHandler->isKeyPressed(SDL_SCANCODE_UP)) {
		m_velocity.setY(-1.f);
	} else if (pInputHandler->isKeyPressed(SDL_SCANCODE_DOWN)) {
		m_velocity.setY(1.f);
	} else if (pInputHandler->isKeyPressed(SDL_SCANCODE_LEFT)) {
		m_velocity.setX(-1.f);
	} else if (pInputHandler->isKeyPressed(SDL_SCANCODE_RIGHT)) {
		m_velocity.setX(1.f);
	} else {
		m_velocity.set(0, 0);
	}

	m_position += m_velocity;
}
