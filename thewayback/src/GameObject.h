#pragma once
#include "pch.h"
#include "Vector2f.h"

class GameObject {

protected:
	int m_width = 0;
	int m_height = 0;

	Vector2f m_position;
	Vector2f m_velocity;
	Vector2f m_acceleration;

public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void init(float x, float y, int w, int h) {
		m_position = { x, y };
		m_width = w;
		m_height = h;
	}
	virtual void update() {
		m_velocity += m_acceleration;
		m_position += m_velocity;
	}
	virtual void draw() = 0;
	virtual void clean() = 0;

	Vector2f getPosition() const {
		return m_position;
	}

	int getWidth() const {
		return m_width;
	}
	int getHeight() const {
		return m_height;
	}

};

