#pragma once
#include "pch.h"

class GameObject {

public:
	GameObject(float x, float y, int w, int h, std::string textureId) {}
	virtual ~GameObject() { }

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clean() = 0;

};

