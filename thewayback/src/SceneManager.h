#pragma once
#include "GameScene.h"

class SceneManager {

private:
    std::vector<std::shared_ptr<GameScene>> m_gameScenes;

public:
    void push(std::shared_ptr<GameScene> pScene);
    void pop();
    void change(std::shared_ptr<GameScene> pScene);

    void update();
    void draw();

    std::weak_ptr<GameScene> getActiveScene() const;

};
