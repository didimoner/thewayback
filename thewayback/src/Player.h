#pragma once
#include "Animation.h"
#include "Collidable.h"
#include "GameObjectCreator.h"

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

	EPlayerState m_playerState = EPlayerState::IDLE;
	static Log* Logger;

public:
	Player() : Animation() {
		m_objectId = "Player";
	}
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