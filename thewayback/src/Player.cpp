#include "pch.h"
#include "Player.h"
#include "InputHandler.h"
#include "ECollisionType.h"
#include "Log.h"
#include "Game.h"
#include "PlayScene.h"
#include "Npc.h"

Log Player::Logger(typeid(Player).name());

void Player::init(const InitParams& initParams) {
    Animation::init(initParams.animationInitParams);
    m_walkingSpeed = initParams.walkingSpeed;
    m_runningSpeed= initParams.runningSpeed;
}

void Player::update() {
    if (!m_locked) {
        handleKeyboardInput();
    }
    
    updatePlayerState();
    Animation::update();
}

void Player::draw() {
    Animation::draw();
}

void Player::clean() {
}

void Player::lock() {
    m_playerState = EPlayerState::IDLE;
    m_locked = true;
}

void Player::unlock() {
    m_locked = false;
}

void Player::onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) {
    switch (type) {
        case ECollisionType::PLAYER_OBSTACLE: {
            m_acceleration.set(0, 0);
            m_position -= m_velocity;

            break;
        }

        case ECollisionType::PLAYER_NPC:{
            if (InputHandler::instance().isKeyPressed(SDL_SCANCODE_E) && !m_locked) {
                const auto pScene = std::dynamic_pointer_cast<PlayScene>(Game::instance().getActiveScene().lock());
                pScene->getUserInterface()->startDialog(std::dynamic_pointer_cast<Npc>(pCollidable)->getId());
            }

            break;
        }
    }
}

SDL_FRect Player::getCollider() const {
    return {m_position.getX(), m_position.getY(), static_cast<float_t>(m_width), static_cast<float_t>(m_height)};
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

    m_running = inputHandler.isKeyPressed(SDL_SCANCODE_LSHIFT);
}

void Player::updatePlayerState() {
    if (m_running) {
        setAnimationSpeed(EAnimationSpeed::FAST);
    } else {
        setAnimationSpeed(EAnimationSpeed::NORMAL);
    }

    const float_t speed = m_running ? m_runningSpeed : m_walkingSpeed;
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
        playAnimation();
    } else {
        stopAnimation();
    }
}
