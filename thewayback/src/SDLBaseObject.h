#pragma once

#include <SDL.h>
#include "BaseObject.h"

class SDLBaseObject : public BaseObject {

public:
	SDLBaseObject(int x, int y, int w, int h, std::string textureId);

	SDL_Rect getRect() const;

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:
	int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	std::string m_textureId;

};
