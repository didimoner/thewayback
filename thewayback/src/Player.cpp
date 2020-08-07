#include "pch.h"
#include "Player.h"

Player::Player(float x, float y, int w, int h, std::string textureId)
	: SDLBaseObject(x, y, w, h, textureId) {

	//m_velocity.setY(1.f);
	//m_acceleration.setY(0.02f);
}

void Player::draw() {
	SDLBaseObject::draw();
}

void Player::update() {
	m_currentFrame = int(((SDL_GetTicks() / 250) % 3));

	SDLBaseObject::update();
}

void Player::clean() {
	SDLBaseObject::clean();
}