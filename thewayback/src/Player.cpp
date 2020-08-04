#include "pch.h"
#include "Player.h"

Player::Player(int x, int y, int w, int h, std::string textureId) 
	: SDLBaseObject(x, y, w, h, textureId) {

}

void Player::draw() {
	SDLBaseObject::draw();
}

void Player::update() {
	m_x += 1;
}

void Player::clean() {

}