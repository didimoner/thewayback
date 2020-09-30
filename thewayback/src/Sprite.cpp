#include "pch.h"
#include "Sprite.h"
#include <utility>
#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameState.h"
#include "Camera.h"

void Sprite::init(float x, float y, int w, int h, std::string textureId) {
    GameObject::init(x, y, w, h);
    m_textureId = std::move(textureId);
}

void Sprite::update() {
    GameObject::update();
}

void Sprite::draw() {
    const Vector2f cameraPos = Game::instance().getCurrentState().getCamera()->getPosition();
    TextureManager::instance().drawFrame(m_textureId,
                                         m_position.getX() - cameraPos.getX(), m_position.getY() - cameraPos.getY(),
                                         m_width, m_height, m_row, m_frame, Game::instance().getRenderer());
}
