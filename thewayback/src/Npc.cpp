#include "pch.h"
#include "Npc.h"
#include "ECollisionType.h"
#include "Log.h"
#include "Game.h"
#include "GameScene.h"
#include "UserInterface.h"
#include "InputHandler.h"

Log Npc::Logger(typeid(Npc).name());

void Npc::init(const InitParams& initParams) {
    Sprite::init(initParams.spriteInitParams);
}

void Npc::update() {
    Sprite::update();
}

void Npc::draw() {
    Sprite::draw();
}

void Npc::clean() {
}

void Npc::onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) {
    if (!m_collisionEnabled) {
        return;
    }

    switch (type) {
        case ECollisionType::PLAYER_NPC: {
            if (InputHandler::instance().isKeyPressed(SDL_SCANCODE_E)) {
                std::function<void()> callback = [this]() {
                    this->m_collisionEnabled = true;
                };
                m_collisionEnabled = false;

                Game::instance().getActiveScene().getUserInterface().createTextBox(callback);
            }

            break;
        }
    }
}

SDL_FRect Npc::getCollider() const {
    return { m_position.getX(), m_position.getY(), static_cast<float_t>(m_width), static_cast<float_t>(m_height) };
}
