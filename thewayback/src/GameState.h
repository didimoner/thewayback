#pragma once
#include "pch.h"
#include "Camera.h"
#include "Game.h"

class Vector2f;

class GameState {

protected:
    Camera m_camera;

public:
    Camera* getCamera() { return &m_camera; }

    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void onActivate() = 0;
    virtual bool onDeactivate() = 0;

    virtual std::string getStateId() const = 0;
    
};