#pragma once
#include "GameState.h"

class Log;
class GameObject;

class MenuState : public GameState {

private:
    static const std::string s_stateId;
    static Log Logger;

    std::vector<GameObject*> m_gameObjects;

public:
    void update() override;
    void draw() override;

    void onActivate() override;
    bool onDeactivate() override;

    std::string getStateId() const override;

};
