#pragma once
#include "pch.h"
#include "Vector2f.h"

class GameObject {

protected:
	Vector2f m_position;
	int m_width = 0;
	int m_height = 0;

public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void init(float x, float y, int w, int h) {
		m_position = { x, y };
		m_width = w;
		m_height = h;
	}
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clean() = 0;

};

