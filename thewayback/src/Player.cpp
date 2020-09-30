#include "pch.h"
#include "Player.h"
#include "InputHandler.h"
#include "ECollisionType.h"
#include "Log.h"
#include "Game.h"
#include "GameState.h"

Log Player::Logger(typeid(Player).name());

Player::Player() : Animation() {
    m_objectId = "Player";
}

void Player::update() {
    handleKeyboardInput();
    updatePlayerState();

    Animation::update();
}

void Player::draw() {
    Sprite::draw();
}

void Player::clean() {
    Sprite::clean();
}

void Player::onCollide(ECollisionType type, std::string objectId) {
    Camera* pCamera = Game::instance().getCurrentState().getCamera();

    switch (type) {
    case ECollisionType::PLAYER_OBSTACLE: {
        m_acceleration.set(0, 0);
        m_position -= m_velocity;
    }
    }
}

SDL_FRect Player::getBoundary() const {
    return {m_position.getX(), m_position.getY(), (float)m_width, (float)m_height};
}

void Player::setWalkingSpeed(float walkingSpeed) {
    m_walkingSpeed = walkingSpeed;
}

void Player::setRunningSpeed(float runningSpeed) {
    m_runningSpeed = runningSpeed;
}

void Player::handleKeyboardInput() {
    InputHandler& inputHandler = InputHandler::instance();

    if (inputHandler.isKeyPressed(SDL_SCANCODE_UP) && m_velocity.getX() == 0 && m_velocity.getY() != 1) {
        m_playerState = EPlayerState::MOVING_UP;
    } else if (inputHandler.isKeyPressed(SDL_SCANCODE_DOWN) && m_velocity.getX() == 0 && m_velocity.getY() != -1) {
        m_playerState = EPlayerState::MOVING_DOWN;
    } else if (inputHandler.isKeyPressed(SDL_SCANCODE_LEFT) && m_velocity.getY() == 0 && m_velocity.getX() != 1) {
        m_playerState = EPlayerState::MOVING_LEFT;
    } else if (inputHandler.isKeyPressed(SDL_SCANCODE_RIGHT) && m_velocity.getY() == 0 && m_velocity.getX() != -1) {
        m_playerState = EPlayerState::MOVING_RIGHT;
    } else {
        m_playerState = EPlayerState::IDLE;
    }

    m_isRunning = inputHandler.isKeyPressed(SDL_SCANCODE_LSHIFT);
}

void Player::updatePlayerState() {
    if (m_isRunning) {
        setAnimationSpeed(EAnimationSpeed::FAST);
    } else {
        setAnimationSpeed(EAnimationSpeed::NORMAL);
    }

    float speed = m_isRunning ? m_runningSpeed : m_walkingSpeed;
    switch (m_playerState) {
    case EPlayerState::MOVING_UP:
        m_velocity.setY(-1 * speed);
        m_row = 3;
        break;
    case EPlayerState::MOVING_RIGHT:
        m_velocity.setX(speed);
        m_row = 2;
        break;
    case EPlayerState::MOVING_DOWN:
        m_velocity.setY(speed);
        m_row = 0;
        break;
    case EPlayerState::MOVING_LEFT:
        m_velocity.setX(-1 * speed);
        m_row = 1;
        break;
    case EPlayerState::IDLE:
        m_velocity.set(0, 0);
        break;
    }

    if (m_playerState != EPlayerState::IDLE) {
        Animation::playAnimation();
    } else {
        Animation::stopAnimation();
    }
}
