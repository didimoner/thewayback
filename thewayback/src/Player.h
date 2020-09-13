#pragma once
#include "SDLGameObject.h"
#include "GameObjectCreator.h"

class Log;

class Player : public SDLGameObject {

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
	Player() : SDLGameObject() {
		m_objectId = "Player";
	}
	~Player() {}

	void init(float x, float y, int w, int h, std::string textureId);
	void update();
	void draw();
	void clean();

	void onCollide(ECollisionType type, std::string objectId);

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