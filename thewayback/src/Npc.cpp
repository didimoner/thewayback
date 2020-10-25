#include "pch.h"
#include "Npc.h"
#include "ECollisionType.h"
#include "Log.h"

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
    switch (type) {
        case ECollisionType::PLAYER_NPC: {
            // todo: react
            Logger.debug("COLLISION WITH PLAYER!!!");
        }
    }
}

SDL_FRect Npc::getCollider() const {
    return { m_position.getX(), m_position.getY(), static_cast<float_t>(m_width), static_cast<float_t>(m_height) };
}
