#pragma once
#include "Sprite.h"
#include "Collidable.h"
#include "Dialog.h"
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

    std::string m_id;
    std::vector<std::shared_ptr<Dialog>> m_dialogs;

public:
    void init(const Npc::InitParams& initParams);
    void update() override;
    void draw() override;
    void clean() override;

    void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) override;

    SDL_FRect getCollider() const override;
    std::string getId() const;
    std::vector<std::shared_ptr<Dialog>>& getDialogs();

};

class NpcCreator final : public GameObjectCreator {

public:
    std::shared_ptr<GameObject> create() const override {
        return std::shared_ptr<Npc>(new Npc);
    }

};