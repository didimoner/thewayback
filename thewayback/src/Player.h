#pragma once
#include "SDLGameObject.h"
#include "GameObjectCreator.h"

class Player : public SDLGameObject {

private:
	enum class PlayerState {
		IDLE,
		MOVING_UP,
		MOVING_RIGHT,
		MOVING_DOWN,
		MOVING_LEFT
	};

	PlayerState m_playerState = PlayerState::IDLE;

public:
	Player() : SDLGameObject() {}
	~Player() {}

	void init(float x, float y, int w, int h, std::string textureId);
	void update();
	void draw();
	void clean();

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