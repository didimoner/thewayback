#pragma once
#include <SDL.h>
#include "Vector2f.h"
#include "GameObject.h"
#include "Collidable.h"
#include "ECollisionType.h"

class SDLGameObject : public GameObject, public Collidable {

protected:
	Vector2f m_velocity;
	Vector2f m_acceleration;

	int m_currentRow = 0;
	int m_currentFrame = 0;

	Uint16 m_frames = 0;
	std::string m_textureId;

public:
	SDLGameObject() : GameObject() {}
	virtual ~SDLGameObject() {}

	virtual void init(float x, float y, int w, int h, std::string textureId, Uint16 frames);
	virtual void update();
	virtual void draw();
	virtual void clean();

	Vector2f getPosition() const;

	virtual void onCollide(ECollisionType type, std::string objectId) { }
	SDL_FRect getBoundary() const;

};
