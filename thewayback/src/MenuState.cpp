#include "pch.h"
#include "MenuState.h"
#include "Player.h"

Log* MenuState::Logger = new Log(typeid(MenuState).name());
const std::string MenuState::s_stateId = "MENU_STATE";

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
    GameObject* pPlayer = new Player(25, 50, 32, 32, "player");
    m_gameObjects.push_back(pPlayer);

    Logger->debug("Menu activated");
}

bool MenuState::onDeactivate() {
    for (GameObject* pObject : m_gameObjects) {
        pObject->clean();
        delete pObject;
    }

    m_gameObjects.clear();

    Logger->debug("Menu deactivated");
    return true;
}
