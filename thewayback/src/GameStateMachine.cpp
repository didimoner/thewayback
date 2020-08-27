#include "pch.h"
#include "GameState.h"
#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState) {
    m_gameStates.push_back(pState);
    pState->onActivate();
}

void GameStateMachine::popState() {
    if (m_gameStates.empty()) {
        return;
    }

    GameState* pCurrentState = m_gameStates.back();
    if (pCurrentState->onDeactivate()) {
        delete pCurrentState;
        m_gameStates.pop_back();
    }
}

void GameStateMachine::changeState(GameState* pState) {
    if (m_gameStates.empty()) {
        return;
    }

    GameState* pCurrentState = m_gameStates.back();
    if (pCurrentState->getStateId() == pState->getStateId()) {
        return;
    }

    if (pCurrentState->onDeactivate()) {
        delete pCurrentState;
        m_gameStates.pop_back();
    }

    m_gameStates.push_back(pState);
    pState->onActivate();
}

void GameStateMachine::update() {
    if (m_gameStates.empty()) {
        return;
    }

    m_gameStates.back()->update();
}

void GameStateMachine::draw() {
    if (m_gameStates.empty()) {
        return;
    }

    m_gameStates.back()->draw();
}

const GameState* const GameStateMachine::getCurrentState() const {
    return m_gameStates.back();
}
