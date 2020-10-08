#include "pch.h"
#include "GameScene.h"
#include "GameSceneManager.h"

void GameSceneManager::push(std::unique_ptr<GameScene> pScene) {
    m_gameScenes.emplace_back(std::move(pScene));
    m_gameScenes.back()->onActivate();
}

void GameSceneManager::pop() {
    if (m_gameScenes.empty()) {
        return;
    }

    if (m_gameScenes.back()->onDeactivate()) {
        m_gameScenes.pop_back();
    }
}

void GameSceneManager::change(std::unique_ptr<GameScene> pScene) {
    if (m_gameScenes.empty()
        || m_gameScenes.back()->getSceneId() == pScene->getSceneId()) {
        return;
    }

    pop();
    push(std::move(pScene));
}

void GameSceneManager::update() {
    if (m_gameScenes.empty()) {
        return;
    }

    m_gameScenes.back()->update();
}

void GameSceneManager::draw() {
    if (m_gameScenes.empty()) {
        return;
    }

    m_gameScenes.back()->draw();
}

GameScene& GameSceneManager::getActiveScene() const {
    return *m_gameScenes.back();
}
