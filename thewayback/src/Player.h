#pragma once
#include "Collidable.h"
#include "GameObjectCreator.h"
#include "Animation.h"

class Log;

class Player : public Animation, public Collidable {

private:
	enum class EPlayerState {
		IDLE,
		MOVING_UP,
		MOVING_RIGHT,
		MOVING_DOWN,	
		MOVING_LEFT
	};

private:
	float m_walkingSpeed = 1;
	float m_runningSpeed = 1;
	EPlayerState m_playerState = EPlayerState::IDLE;
	bool m_isRunning= false;

	static Log Logger;

public:
	Player();
	~Player() {}

	void update();
	void draw();
	void clean();

	void onCollide(ECollisionType type, std::string objectId);
	SDL_FRect getBoundary() const;

	void setWalkingSpeed(float walkingSpeed);
	void setRunningSpeed(float runningSpeed);

private:
	void handleKeyboardInput();
	void updatePlayerState();

};

class PlayerCreator : public GameObjectCreator {

public:
	GameObject* create() const {
		return new Player();
	}

};