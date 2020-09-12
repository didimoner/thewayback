#include "pch.h"
#include "MenuState.h"
#include "Game.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "Log.h"
#include "GameObject.h"

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
    StateParser stateParser;
    stateParser.parse("states.xml", getStateId(), m_gameObjects);

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
