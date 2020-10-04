#pragma once
#include "GameState.h"

class GameStateMachine {

private:
    std::vector<std::unique_ptr<GameState>> m_gameStates;

public:
    void pushState(std::unique_ptr<GameState> pState);
    void popState();
    void changeState(std::unique_ptr<GameState> pState);

    void update();
    void draw();

    GameState& getCurrentState() const;

};
