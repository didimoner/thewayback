#pragma once

#include <SDL.h>
#include "BaseObject.h"
#include "Vector2f.h"

class SDLBaseObject : public BaseObject {

public:
	SDLBaseObject(float x, float y, int w, int h, std::string textureId);

	SDL_Rect getRect() const;

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:
	Vector2f m_position;
	Vector2f m_velocity;
	Vector2f m_acceleration;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	std::string m_textureId;

};
