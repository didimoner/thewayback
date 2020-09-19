#pragma once
#include "Drawable.h"

class Animation : public Drawable {

public:
	enum class EType {
		NORMAL, BOUNCE
	};

	struct InitParams {
		uint8_t frames = 0;
		uint8_t defaltFrame = 0;
		uint16_t speed = 0;
		EType type = EType::NORMAL;
		bool looped = false;
	};

private:
	enum class EState {
		PLAY, PAUSE, STOP
	};

private:
	uint16_t m_speed = 1;
	uint8_t m_defaultFrame = 0;
	bool m_looped = false;

	EState m_state = EState::STOP;
	std::vector<uint8_t> m_frames;
	uint32_t m_previousTick = 0;
	size_t m_frameIndex = 0;

public:
	Animation() : Drawable() {}
	virtual ~Animation() {}

	virtual void init(float x, float y, int w, int h, std::string textureId, InitParams params);
	virtual void update();
	virtual void draw();
	virtual void clean() {}

	void playAnimation();
	void pauseAnimation();
	void stopAnimation();

private:
	void updateState();

};