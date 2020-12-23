#include "pch.h"
#include "GameScene.h"
#include "SceneManager.h"

void SceneManager::push(std::shared_ptr<GameScene> pScene) {
    m_gameScenes.push_back(std::move(pScene));
    m_gameScenes.back()->onActivate();
}

void SceneManager::pop() {
    if (m_gameScenes.empty()) {
        return;
    }

    if (m_gameScenes.back()->onDeactivate()) {
        m_gameScenes.pop_back();
    }
}

void SceneManager::change(std::shared_ptr<GameScene> pScene) {
    if (m_gameScenes.empty()
        || m_gameScenes.back()->getSceneId() == pScene->getSceneId()) {
        return;
    }

    pop();
    push(std::move(pScene));
}

void SceneManager::update() {
    if (m_gameScenes.empty()) {
        return;
    }

    m_gameScenes.back()->update();
}

void SceneManager::draw() {
    if (m_gameScenes.empty()) {
        return;
    }

    m_gameScenes.back()->draw();
}

std::weak_ptr<GameScene> SceneManager::getActiveScene() const {
    return m_gameScenes.back();
}
