#pragma once
#include "GameScene.h"

class Log;

class SplashScene : public GameScene {

private:
    static const std::string SCENE_ID;
    static Log Logger;

public:
    void update() override;
    void draw() override;

    void onActivate() override;
    bool onDeactivate() override;

    std::string getSceneId() const override;

};
