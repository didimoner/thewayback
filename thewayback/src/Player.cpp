#include "pch.h"
#include "Player.h"
#include "InputHandler.h"

void Player::load(float x, float y, int w, int h, std::string textureId) {
	SDLGameObject::load(x, y, w, h, textureId);
}

void Player::update() {
	m_currentFrame = int(((SDL_GetTicks() / 250) % 3));

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

	SDLGameObject::update();
}

void Player::draw() {
	SDLGameObject::draw();
}

void Player::clean() {
	SDLGameObject::clean();
}