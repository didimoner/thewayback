#pragma once
#include "Sprite.h"
#include "Collidable.h"
#include "GameObjectCreator.h"

class Log;

class Npc : public Sprite, public Collidable {

public:
    struct InitParams {
        Sprite::InitParams spriteInitParams;
    };

private:
    friend class NpcCreator;
    static Log Logger;

    bool m_collisionEnabled = true;

public:
    void init(const InitParams& initParams);
    void update() override;
    void draw() override;
    void clean() override;

    void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) override;
    SDL_FRect getCollider() const override;

};

class NpcCreator final : public GameObjectCreator {

public:
    std::shared_ptr<GameObject> create() const override {
        return std::shared_ptr<Npc>(new Npc);
    }

};