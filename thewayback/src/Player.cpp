#include "pch.h"
#include "Player.h"
#include "InputHandler.h"
#include "ECollisionType.h"
#include "Log.h"

Log* Player::Logger = new Log(typeid(Player).name());

void Player::init(float x, float y, int w, int h, std::string textureId) {
	SDLGameObject::init(x, y, w, h, textureId);
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

void Player::onCollide(ECollisionType type, std::string objectId) {
	switch (type) {
		case ECollisionType::PLAYER_OBSTACLE: {
			Logger->debug("Collision detected! Object: " + objectId);
			// TODO: stop the movement
		}
	}
}

void Player::handleKeyboardInput() {
	InputHandler* pInputHandler = InputHandler::instance();

	if (pInputHandler->isKeyPressed(SDL_SCANCODE_UP) && m_velocity.getX() == 0 && m_velocity.getY() != 1) {
		m_velocity.setY(-1.f);
		m_playerState = EPlayerState::MOVING_UP;
	} else if (pInputHandler->isKeyPressed(SDL_SCANCODE_DOWN) && m_velocity.getX() == 0 && m_velocity.getY() != -1) {
		m_velocity.setY(1.f);
		m_playerState = EPlayerState::MOVING_DOWN;
	} else if (pInputHandler->isKeyPressed(SDL_SCANCODE_LEFT) && m_velocity.getY() == 0 && m_velocity.getX() != 1) {
		m_velocity.setX(-1.f);
		m_playerState = EPlayerState::MOVING_LEFT;
	} else if (pInputHandler->isKeyPressed(SDL_SCANCODE_RIGHT) && m_velocity.getY() == 0 && m_velocity.getX() != -1) {
		m_velocity.setX(1.f);
		m_playerState = EPlayerState::MOVING_RIGHT;
	} else {
		m_velocity.set(0, 0);
		m_playerState = EPlayerState::IDLE;
	}
}

void Player::updatePlayerState() {
	switch (m_playerState) {
		case EPlayerState::MOVING_UP:
			m_currentRow = 3;
			break;
		case EPlayerState::MOVING_RIGHT:
			m_currentRow = 2;
			break;
		case EPlayerState::MOVING_DOWN:
			m_currentRow = 0;
			break;
		case EPlayerState::MOVING_LEFT:
			m_currentRow = 1;
			break;
	}

	if (m_playerState != EPlayerState::IDLE) {
		// TODO: move amount of frames outside
		m_currentFrame = (SDL_GetTicks() / (100 * 2)) % 3;
	} else {
		m_currentFrame = 1;
	}
}
