#include "pch.h"
#include "Animation.h"
#include "Drawable.h"
#include <SDL_timer.h>
#include "Log.h"

void Animation::init(float x, float y, int w, int h, std::string textureId, AnimationInitParams params) {
    Sprite::init(x, y, w, h, textureId);
    m_speed = params.speed;
    m_looped = params.looped;
    m_defaultFrame = params.defaultFrame;

    for (int i = 0; i < params.totalFrames; i++) {
        m_totalFrames.push_back(i);
    }

    if (params.type == EAnimationType::BOUNCE) {
        for (int i = params.totalFrames - 2; i > 0; i--) {
            m_totalFrames.push_back(i);
        }
    }
}

void Animation::update() {
    Sprite::update();

    if (m_state == Animation::EState::PLAY) {
        updateState();
    }
}

void Animation::draw() {
    Sprite::draw();
}

void Animation::playAnimation() {
    m_state = Animation::EState::PLAY;
}

void Animation::pauseAnimation() {
    m_state = Animation::EState::PAUSE;
    m_previousTick = 0;
}

void Animation::stopAnimation() {
    m_state = Animation::EState::STOP;
    m_frameIndex = m_defaultFrame;
    m_frame = m_totalFrames[m_frameIndex];
    m_previousTick = 0;
}

void Animation::updateState() {
    if (m_speed < 1) {
        return;
    }

    uint32_t now = SDL_GetTicks();
    uint32_t elapsedTime = now - m_previousTick;

    if (elapsedTime >= 1000u / m_speed) {
        if (m_frameIndex >= m_totalFrames.size()) {
            m_frameIndex = 0;
        }
        m_frame = m_totalFrames[m_frameIndex++];
        m_previousTick = now;
    }
}
