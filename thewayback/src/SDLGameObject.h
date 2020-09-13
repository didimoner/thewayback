#pragma once
#include <SDL.h>
#include "Vector2f.h"
#include "GameObject.h"
#include "Collidable.h"

class SDLGameObject : public GameObject, public Collidable {

protected:
	Vector2f m_velocity;
	Vector2f m_acceleration;

	int m_currentRow = 0;
	int m_currentFrame = 0;

	std::string m_textureId;

public:
	SDLGameObject() : GameObject() {}
	virtual ~SDLGameObject() {}

	virtual void init(float x, float y, int w, int h, std::string textureId);
	virtual void update();
	virtual void draw();
	virtual void clean();

	virtual void onCollide(CollisionType type, std::string objectId) {}
	SDL_Rect getRect() const;

};
