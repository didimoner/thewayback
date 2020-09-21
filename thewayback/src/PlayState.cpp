#include "pch.h"
#include "PlayState.h"
#include "Log.h"
#include "LevelParser.h"
#include "Level.h"
#include "StateParser.h"

Log* PlayState::Logger = new Log(typeid(PlayState).name());
const std::string PlayState::s_stateId = "PLAY_STATE";

void PlayState::update() {
    m_camera.update();
    m_pLevel->update();
}

void PlayState::draw() {
    m_pLevel->draw();
}

void PlayState::onActivate() {
    Logger->debug("Play activated");

    m_camera.setPosition(0, 0);

    StateParser stateParser;
    std::vector<GameObject*> gameObjects;
    stateParser.parse("states.xml", getStateId(), gameObjects);

    LevelParser levelParser;
    m_pLevel = levelParser.parse("test5.tmx");
}

bool PlayState::onDeactivate() {
    Logger->debug("Play deactivated");
    return false;
}
