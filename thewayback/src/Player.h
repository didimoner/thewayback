#pragma once
#include "SDLGameObject.h"
#include "GameObjectCreator.h"

class Player : public SDLGameObject {

public:
	Player() : SDLGameObject() {}
	~Player() {}

	void load(float x, float y, int w, int h, std::string textureId);
	void update();
	void draw();
	void clean();

};

class PlayerCreator : public GameObjectCreator {

public:
	~PlayerCreator() {}

	GameObject* create() const {
		return new Player();
	}

};