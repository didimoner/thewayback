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
    const Vector2f cameraPos = Game::instance().getActiveScene().lock()->getCamera().getPosition();

    SDL_Rect sourceRect;
    sourceRect.x = m_width * m_frame;
    sourceRect.y = m_height * m_row;
    sourceRect.w = m_width;
    sourceRect.h = m_height;

    SDL_Rect destRect;
    destRect.x = static_cast<int>(m_position.getX() - cameraPos.getX());
    destRect.y = static_cast<int>(m_position.getY() - cameraPos.getY());
    destRect.w = m_width;
    destRect.h = m_height;

    Renderer::instance().send(m_textureId, sourceRect, destRect, m_zIndex);
}
