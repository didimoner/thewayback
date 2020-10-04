#pragma once
#include "pch.h"
#include "Camera.h"

class Vector2f;
class Drawable;

class GameState {

protected:
    std::unique_ptr<Camera> m_pCamera;
    std::vector<std::shared_ptr<Drawable>> m_drawables;

private:
    friend class GameStateParser;

public:
    virtual ~GameState() = default;

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void onActivate() = 0;
    virtual bool onDeactivate() = 0;
    virtual std::string getStateId() const = 0;

    const Camera& getCamera() const { return *m_pCamera; }

};
