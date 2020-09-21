#include "pch.h"
#include "Drawable.h"
#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameState.h"

void Drawable::init(float x, float y, int w, int h, std::string textureId) {
	GameObject::init(x, y, w, h);
	m_textureId = textureId;
}

void Drawable::update() {
	GameObject::update();
}

void Drawable::draw() {
	Vector2f cameraPos = Game::instance()->getCurrentState()->getCamera()->getPosition();
	TextureManager::instance()->drawFrame(m_textureId,
		m_position.getX() - cameraPos.getX(), m_position.getY() - cameraPos.getY(),
		m_width, m_height, m_row, m_frame, Game::instance()->getRenderer());
}