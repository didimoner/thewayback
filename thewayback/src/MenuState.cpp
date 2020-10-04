#include "pch.h"
#include "MenuState.h"
#include "GameStateParser.h"
#include "Log.h"
#include "GameObject.h"

Log MenuState::Logger(typeid(MenuState).name());
const std::string MenuState::STATE_ID = "MENU_STATE";

void MenuState::update() {
    for (GameObject* pObject : m_gameObjects) {
        pObject->update();
    }
}

void MenuState::draw() {
    for (GameObject* pObject : m_gameObjects) {
        pObject->draw();
    }
}

void MenuState::onActivate() {
    Logger.debug("Menu activated");
}

bool MenuState::onDeactivate() {
    for (GameObject* pObject : m_gameObjects) {
        pObject->clean();
        delete pObject;
    }

    m_gameObjects.clear();

    Logger.debug("Menu deactivated");
    return true;
}

std::string MenuState::getStateId() const {
    return STATE_ID;
}
