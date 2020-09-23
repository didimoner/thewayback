#pragma once
#include "GameObject.h"

// TODO: Sprite
class Drawable : public GameObject {

protected:
	uint8_t m_row = 0;
	uint8_t m_frame = 0;
	std::string m_textureId;

public:
	Drawable() : GameObject() {}
	virtual ~Drawable() {}

	virtual void init(float x, float y, int w, int h, std::string textureId);
	virtual void update();
	virtual void draw();
	virtual void clean() {}

};