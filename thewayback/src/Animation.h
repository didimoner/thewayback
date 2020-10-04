#pragma once
#include "Sprite.h"

enum class EAnimationType {
    NORMAL,
    BOUNCE
};

enum class EAnimationSpeed {
    SLOW,
    NORMAL,
    FAST
};

class Animation : public Sprite {

public:
    struct InitParams {
        Sprite::InitParams spriteInitParams;
        uint8_t totalFrames = 0;
        uint8_t defaultFrame = 0;
        uint16_t speed = 0;
        EAnimationType type = EAnimationType::NORMAL;
        bool looped = false;
    };

private:
    enum class EState {
        PLAY,
        PAUSE,
        STOP
    };

private:
    uint16_t m_speed = 0;
    uint8_t m_defaultFrame = 0;
    bool m_looped = false;
    EState m_state = EState::STOP;
    EAnimationSpeed m_animationSpeed = EAnimationSpeed::NORMAL;
    std::vector<uint8_t> m_totalFrames;
    uint32_t m_previousTick = 0;
    size_t m_frameIndex = 0;

public:
    void init(const InitParams& initParams);
    void update() override;
    void draw() override;

    void playAnimation();
    void pauseAnimation();
    void stopAnimation();

    void setAnimationSpeed(EAnimationSpeed animationSpeed);

private:
    void updateState();

};
