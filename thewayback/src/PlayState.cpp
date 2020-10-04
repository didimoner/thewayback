#include "pch.h"
#include "PlayState.h"
#include "Log.h"
#include "Camera.h"
#include "Game.h"

Log PlayState::Logger(typeid(PlayState).name());
const std::string PlayState::STATE_ID = "PLAY_STATE";

void PlayState::update() {
    m_pLevel->update();
    m_pCamera->update();
}

void PlayState::draw() {
    m_pLevel->draw();
}

void PlayState::onActivate() {
    Logger.debug("Play activated");

    // TODO: level is not set because of GameState base class
    // TODO: set player properly
    // m_pLevel->setPlayer(m_pPlayer);
    m_pCamera = std::make_unique<Camera>(
        Game::instance().getWindowWidth(),
        Game::instance().getWindowHeight(),
        m_pLevel->getWidthPx(),
        m_pLevel->getHeightPx(),
        m_pPlayer
    );
}

bool PlayState::onDeactivate() {
    Logger.debug("Play deactivated");
    return false;
}

std::string PlayState::getStateId() const {
    return STATE_ID;
}
