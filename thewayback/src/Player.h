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
	float m_walkSpeed = 1;
	float m_runSpeed = 3;
	EPlayerState m_playerState = EPlayerState::IDLE;
	bool m_isRunning= false;
	static Log* Logger;

public:
	Player();
	~Player() {}

	void update();
	void draw();
	void clean();

	void onCollide(ECollisionType type, std::string objectId);
	SDL_FRect getBoundary() const;

private:
	void handleKeyboardInput();
	void updatePlayerState();

};

class PlayerCreator : public GameObjectCreator {

public:
	~PlayerCreator() {}

	GameObject* create() const {
		return new Player();
	}

};