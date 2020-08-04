#include "pch.h"
#include "SDLBaseObject.h"

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

void SDLBaseObject::draw() {
	// todo: draw

}

void SDLBaseObject::update() {
}

void SDLBaseObject::clean() {
}
