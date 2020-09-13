#include "pch.h"
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameState.h"
#include "GameObject.h"

void SDLGameObject::init(float x, float y, int w, int h, std::string textureId, Uint16 frames) {
	GameObject::init(x, y, w, h);
	m_textureId = textureId;
	m_frames = frames;
}

void SDLGameObject::update() {
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void SDLGameObject::draw() {
	Vector2f cameraPos = Game::instance()->getCurrentState()->getCameraPosition();
	TextureManager::instance()->drawFrame(m_textureId, 
		m_position.getX() - cameraPos.getX(), m_position.getY() - cameraPos.getY(),
		m_width, m_height, m_currentRow, m_currentFrame, Game::instance()->getRenderer());
}

void SDLGameObject::clean() {
}

std::vector<SDL_Rect> SDLGameObject::getBoundaries() const {
	SDL_Rect rect = { (int)m_position.getX(), (int)m_position.getY(), m_width, m_height };
	return { rect };
}
