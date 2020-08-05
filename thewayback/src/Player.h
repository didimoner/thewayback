#pragma once

#include "SDLBaseObject.h"

class Player : public SDLBaseObject {

public:
	Player(int x, int y, int w, int h, std::string textureId);

	virtual void draw();
	virtual void update();
	virtual void clean();

private:


};