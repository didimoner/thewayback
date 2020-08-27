#pragma once
#include "pch.h"
#include "Camera.h"
#include "Game.h"

class Vector2f;

class GameState {

protected:
    Camera m_camera;

public:
    Vector2f getCameraPosition() const { return m_camera.getPosition(); }

    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void onActivate() = 0;
    virtual bool onDeactivate() = 0;

    virtual std::string getStateId() const = 0;
    
};