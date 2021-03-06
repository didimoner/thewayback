#include "pch.h"
#include "Animation.h"
#include "Sprite.h"
#include <SDL_timer.h>

void Animation::init(const InitParams& initParams) {
    Sprite::init(initParams.spriteInitParams);
    m_speed = initParams.speed;
    m_looped = initParams.looped;
    m_defaultFrame = initParams.defaultFrame;

    for (uint8_t i = 0; i < initParams.totalFrames; i++) {
        m_totalFrames.push_back(i);
    }

    if (initParams.type == EAnimationType::BOUNCE) {
        for (uint8_t i = initParams.totalFrames - 2; i > 0; i--) {
            m_totalFrames.push_back(i);
        }
    }
}

void Animation::update() {
    Sprite::update();

    if (m_state == EState::PLAY) {
        updateState();
    }
}

void Animation::draw() {
    Sprite::draw();
}

void Animation::playAnimation() {
    m_state = EState::PLAY;
}

void Animation::pauseAnimation() {
    m_state = EState::PAUSE;
    m_previousTick = 0;
}

void Animation::stopAnimation() {
    m_state = EState::STOP;
    m_frameIndex = m_defaultFrame;
    m_frame = m_totalFrames[m_frameIndex];
    m_previousTick = 0;
}

void Animation::setAnimationSpeed(EAnimationSpeed animationSpeed) {
    m_animationSpeed = animationSpeed;
}

void Animation::updateState() {
    if (m_speed < 1) {
        return;
    }

    float_t speedMultiplier = 1;
    switch (m_animationSpeed) {
        case EAnimationSpeed::SLOW:
            speedMultiplier = 0.5;
            break;
        case EAnimationSpeed::FAST:
            speedMultiplier = 2;
            break;
    }

    const uint32_t now = SDL_GetTicks();
    const uint32_t elapsedTime = now - m_previousTick;

    if (elapsedTime >= 1000u / (m_speed * speedMultiplier)) {
        if (m_frameIndex >= m_totalFrames.size()) {
            m_frameIndex = 0;
        }
        m_frame = m_totalFrames[m_frameIndex++];
        m_previousTick = now;
    }
}
