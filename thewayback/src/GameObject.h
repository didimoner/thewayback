#pragma once
#include "pch.h"

class GameObject {

public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void init(float x, float y, int w, int h, std::string textureId) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clean() = 0;

};

