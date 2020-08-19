#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Vector2f.h"

class SDLGameObject : public GameObject {

protected:
	Vector2f m_position;
	Vector2f m_velocity;
	Vector2f m_acceleration;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	std::string m_textureId;

public:
	SDLGameObject(float x, float y, int w, int h, std::string textureId);
	virtual ~SDLGameObject() { }

	virtual void update();
	virtual void draw();
	virtual void clean();

	SDL_Rect getRect() const;

};
