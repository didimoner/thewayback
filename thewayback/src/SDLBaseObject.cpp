#include "pch.h"
#include "SDLBaseObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLBaseObject::SDLBaseObject(int x, int y, int w, int h, std::string textureId)
		: BaseObject(x, y, w, h, textureId) {
	m_x = x;
	m_y = y;
	m_width = w;
	m_height = h;
	m_textureId = textureId;

	m_currentRow = 1;
	m_currentFrame = 1;
}

SDL_Rect SDLBaseObject::getRect() const {
	return { m_x, m_y, m_width, m_height };
}

void SDLBaseObject::draw() {
	TextureManager::instance()->drawFrame(m_textureId, this->getRect(), 
		m_currentRow, m_currentFrame, Game::instance()->getRenderer());

}

void SDLBaseObject::update() {
}

void SDLBaseObject::clean() {
}
