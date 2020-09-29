#include "pch.h"
#include "PlayState.h"
#include "Log.h"
#include "LevelParser.h"
#include "Level.h"
#include "StateParser.h"
#include "Player.h"
#include "Camera.h"

Log PlayState::Logger(typeid(PlayState).name());
const std::string PlayState::s_stateId = "PLAY_STATE";

void PlayState::update() {
    m_pLevel->update();
    m_pCamera->update();
}

void PlayState::draw() {
    m_pLevel->draw();
}

void PlayState::onActivate() {
    Logger.debug("Play activated");

    StateParser stateParser;
    std::vector<GameObject*> gameObjects;
    stateParser.parse("states.xml", getStateId(), gameObjects);

    // TODO: move to state parser
    LevelParser levelParser;
    m_pLevel = levelParser.parse("test5.tmx");

    m_pCamera = new Camera(
        m_pLevel->getPlayer(), 
        Game::instance().getWindowWidth(), 
        Game::instance().getWindowHeight(), 
        m_pLevel->getWidthPx(), 
        m_pLevel->getHeightPx()
    );
}

bool PlayState::onDeactivate() {
    Logger.debug("Play deactivated");
    return false;
}

std::string PlayState::getStateId() const {
    return s_stateId;
}
