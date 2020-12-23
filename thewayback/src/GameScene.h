#pragma once
#include "pch.h"
#include "Camera.h"
#include "Properties.h"
#include "UserInterface.h"

class Vector2f;
class Drawable;

class GameScene {

protected:
    std::unique_ptr<Camera> m_pCamera;
    std::unordered_map<std::string, std::shared_ptr<Drawable>> m_sceneObjects;
    Properties m_sceneProps;

private:
    friend class GameSceneParser;

public:
    virtual ~GameScene() = default;

    virtual void onEvent(uint16_t type, std::string data) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void onActivate() = 0;
    virtual bool onDeactivate() = 0;
    virtual std::string getSceneId() const = 0;

    const Camera& getCamera() const {
        return *m_pCamera;
    }

};
