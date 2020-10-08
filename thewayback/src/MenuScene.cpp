#include "pch.h"
#include "MenuScene.h"
#include "GameSceneParser.h"
#include "Log.h"
#include "GameObject.h"

Log MenuScene::Logger(typeid(MenuScene).name());
const std::string MenuScene::SCENE_ID = "MENU_SCENE";

void MenuScene::update() {
    for (GameObject* pObject : m_gameObjects) {
        pObject->update();
    }
}

void MenuScene::draw() {
    for (GameObject* pObject : m_gameObjects) {
        pObject->draw();
    }
}

void MenuScene::onActivate() {
    Logger.debug("Menu activated");
}

bool MenuScene::onDeactivate() {
    for (GameObject* pObject : m_gameObjects) {
        pObject->clean();
        delete pObject;
    }

    m_gameObjects.clear();

    Logger.debug("Menu deactivated");
    return true;
}

std::string MenuScene::getSceneId() const {
    return SCENE_ID;
}
