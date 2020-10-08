#pragma once
#include "GameScene.h"

class GameSceneManager {

private:
    std::vector<std::unique_ptr<GameScene>> m_gameScenes;

public:
    void push(std::unique_ptr<GameScene> pScene);
    void pop();
    void change(std::unique_ptr<GameScene> pScene);

    void update();
    void draw();

    GameScene& getActiveScene() const;

};
