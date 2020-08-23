#include "pch.h"
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObject.h"

void SDLGameObject::load(float x, float y, int w, int h, std::string textureId) {
	m_position = Vector2f(x, y);
	m_width = w;
	m_height = h;
	m_textureId = textureId;
}

void SDLGameObject::update() {
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void SDLGameObject::draw() {
	TextureManager::instance()->drawFrame(m_textureId, this->getRect(),
		m_currentRow, m_currentFrame, Game::instance()->getRenderer());
}

void SDLGameObject::clean() {
}

SDL_Rect SDLGameObject::getRect() const {
	return { (int)m_position.getX(), (int)m_position.getY(), m_width, m_height };
}