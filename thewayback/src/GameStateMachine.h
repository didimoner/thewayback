#pragma once
#include "GameState.h"

class GameStateMachine {

private:
    std::vector<GameState*> m_gameStates;

public:
    void pushState(GameState* pState);
    void popState();
    void changeState(GameState* pState);

    void update();
    void draw();

};