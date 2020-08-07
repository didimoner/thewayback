#include "pch.h"
#include "SDLBaseObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLBaseObject::SDLBaseObject(float x, float y, int w, int h, std::string textureId)
		: BaseObject(x, y, w, h, textureId) {
	m_position = Vector2f(x, y);
	m_width = w;
	m_height = h;
	m_textureId = textureId;

	m_currentRow = 1;
	m_currentFrame = 1;
}

SDL_Rect SDLBaseObject::getRect() const {
	return { (int) m_position.getX(), (int) m_position.getY(), m_width, m_height };
}

void SDLBaseObject::draw() {
	TextureManager::instance()->drawFrame(m_textureId, this->getRect(), 
		m_currentRow, m_currentFrame, Game::instance()->getRenderer());

}

void SDLBaseObject::update() {
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void SDLBaseObject::clean() {
}
