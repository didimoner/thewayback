#include "pch.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Game.h"
#include "GameScene.h"
#include "Camera.h"
#include "Renderer.h"

void Sprite::init(const InitParams& initParams) {
    GameObject::init(initParams.gameObjectInitParams);
    m_row = initParams.row;
    m_frame = initParams.frame;
    m_textureId = initParams.textureId;
}

void Sprite::update() {
    GameObject::update();
}

void Sprite::draw() {
    const Vector2f cameraPos = Game::instance().getActiveScene().getCamera().getPosition();
    Renderer::instance().send(m_textureId,
                              m_position.getX() - cameraPos.getX(), m_position.getY() - cameraPos.getY(),
                              m_width, m_height, m_zIndex, m_row, m_frame);
}
