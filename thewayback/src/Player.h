#pragma once
#include "Collidable.h"
#include "GameObjectCreator.h"
#include "Animation.h"

class Log;

class Player : public Animation, public Collidable {

public:
    struct InitParams {
        Animation::InitParams animationInitParams;
        float walkingSpeed = 0;
        float runningSpeed = 0;
    };

private:
    enum class EPlayerState {
        IDLE,
        MOVING_UP,
        MOVING_RIGHT,
        MOVING_DOWN,
        MOVING_LEFT
    };

private:
    friend class PlayerCreator;

    float m_walkingSpeed = 1;
    float m_runningSpeed = 1;
    EPlayerState m_playerState = EPlayerState::IDLE;
    bool m_isRunning = false;

    static Log Logger;

public:
    void init(const InitParams& initParams);
    void update() override;
    void draw() override;
    void clean() override;

    void onCollide(ECollisionType type, const std::shared_ptr<Collidable>& pCollidable) override;
    SDL_FRect getCollider() const override;

private:
    void handleKeyboardInput();
    void updatePlayerState();

};

class PlayerCreator final : public GameObjectCreator {

public:
    std::shared_ptr<GameObject> create() const override {
        return std::shared_ptr<Player>(new Player);
    }

};
