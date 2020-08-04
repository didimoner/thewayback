#pragma once

class BaseObject {

public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

protected:
	BaseObject(int x, int y, int w, int h, std::string textureId) {}
	virtual ~BaseObject() {}

};

