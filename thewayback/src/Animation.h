#pragma once
#include "Drawable.h"

enum class EAnimationType {
	NORMAL, BOUNCE
};

struct AnimationInitParams {
	uint8_t totalFrames = 0;
	uint8_t defaultFrame = 0;
	uint16_t speed = 0;
	EAnimationType type = EAnimationType::NORMAL;
	bool looped = false;
};

class Animation : public Sprite {

private:
	enum class EState {
		PLAY, PAUSE, STOP
	};

private:
	uint16_t m_speed = 0;
	uint8_t m_defaultFrame = 0;
	bool m_looped = false;

	EState m_state = EState::STOP;
	std::vector<uint8_t> m_totalFrames;
	uint32_t m_previousTick = 0;
	size_t m_frameIndex = 0;

public:
	Animation() : Sprite() {}
	virtual ~Animation() {}

	virtual void init(float x, float y, int w, int h, std::string textureId, AnimationInitParams params);
	virtual void update();
	virtual void draw();
	virtual void clean() {}

	void playAnimation();
	void pauseAnimation();
	void stopAnimation();

private:
	void updateState();

};