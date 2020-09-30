#pragma once
#include "pch.h"

class Camera;
class Vector2f;

class GameState {

protected:
    Camera* m_pCamera = nullptr;

public:
    virtual ~GameState() = default;
    Camera* getCamera() { return m_pCamera; }

    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void onActivate() = 0;
    virtual bool onDeactivate() = 0;

    virtual std::string getStateId() const = 0;

};
