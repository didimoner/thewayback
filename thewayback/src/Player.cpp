#include "pch.h"
#include "Player.h"
#include "InputHandler.h"

void Player::load(float x, float y, int w, int h, std::string textureId) {
	SDLGameObject::load(x, y, w, h, textureId);
}

void Player::update() {
	handleKeyboardInput();
	updatePlayerState();

	SDLGameObject::update();
}

void Player::draw() {
	SDLGameObject::draw();
}

void Player::clean() {
	SDLGameObject::clean();
}

void Player::handleKeyboardInput() {
	InputHandler* pInputHandler = InputHandler::instance();

	if (pInputHandler->isKeyPressed(SDL_SCANCODE_UP) && m_velocity.getX() == 0 && m_velocity.getY() != 1) {
		m_velocity.setY(-1.f);
		m_playerState = PlayerState::MOVING_UP;
	} else if (pInputHandler->isKeyPressed(SDL_SCANCODE_DOWN) && m_velocity.getX() == 0 && m_velocity.getY() != -1) {
		m_velocity.setY(1.f);
		m_playerState = PlayerState::MOVING_DOWN;
	} else if (pInputHandler->isKeyPressed(SDL_SCANCODE_LEFT) && m_velocity.getY() == 0 && m_velocity.getX() != 1) {
		m_velocity.setX(-1.f);
		m_playerState = PlayerState::MOVING_LEFT;
	} else if (pInputHandler->isKeyPressed(SDL_SCANCODE_RIGHT) && m_velocity.getY() == 0 && m_velocity.getX() != -1) {
		m_velocity.setX(1.f);
		m_playerState = PlayerState::MOVING_RIGHT;
	} else {
		m_velocity.set(0, 0);
		m_playerState = PlayerState::IDLE;
	}
}

void Player::updatePlayerState() {
	switch (m_playerState) {
		case PlayerState::MOVING_UP:
			m_currentRow = 3;
			break;
		case PlayerState::MOVING_RIGHT:
			m_currentRow = 2;
			break;
		case PlayerState::MOVING_DOWN:
			m_currentRow = 0;
			break;
		case PlayerState::MOVING_LEFT:
			m_currentRow = 1;
			break;
	}

	if (m_playerState != PlayerState::IDLE) {
		m_currentFrame = (SDL_GetTicks() / (100 * 2)) % 3;
	} else {
		m_currentFrame = 1;
	}
}
