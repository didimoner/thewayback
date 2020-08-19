#pragma once
#include "SDLGameObject.h"

class Player : public SDLGameObject {

public:
	Player(float x, float y, int w, int h, std::string textureId);
	virtual ~Player() { }

	virtual void update();
	virtual void draw();
	virtual void clean();

};