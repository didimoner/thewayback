#include "pch.h"
#include "Animation.h"
#include "Sprite.h"
#include <SDL_timer.h>
#include "Log.h"

void Animation::init(float x, float y, int w, int h, std::string textureId, AnimationInitParams params) {
    Sprite::init(x, y, w, h, textureId);
    m_speed = params.speed;
    m_looped = params.looped;
    m_defaultFrame = params.defaultFrame;

    for (uint8_t i = 0; i < params.totalFrames; i++) {
        m_totalFrames.push_back(i);
    }

    if (params.type == EAnimationType::BOUNCE) {
        for (uint8_t i = params.totalFrames - 2; i > 0; i--) {
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

    float speedMultiplier = 1;
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
