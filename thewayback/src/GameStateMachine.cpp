#include "pch.h"
#include "GameState.h"
#include "GameStateMachine.h"

void GameStateMachine::pushState(std::unique_ptr<GameState>& pState) {
    m_gameStates.push_back(std::move(pState));
    m_gameStates.back()->onActivate();
}

void GameStateMachine::popState() {
    if (m_gameStates.empty()) {
        return;
    }

    if (m_gameStates.back()->onDeactivate()) {
        m_gameStates.pop_back();
    }
}

void GameStateMachine::changeState(std::unique_ptr<GameState>& pState) {
    if (m_gameStates.empty()
        || m_gameStates.back()->getStateId() == pState->getStateId()) {
        return;
    }

    popState();
    pushState(pState);
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

GameState& GameStateMachine::getCurrentState() const {
    return *m_gameStates.back();
}
