#include "pch.h"
#include "Player.h"

Player::Player(int x, int y, int w, int h, std::string textureId) 
	: SDLBaseObject(x, y, w, h, textureId) {

}

void Player::draw() {
	SDLBaseObject::draw();
}

void Player::update() {
	m_currentFrame = int(((SDL_GetTicks() / 250) % 3));
}

void Player::clean() {

}