#include "pch.h"
#include "PlayScene.h"
#include "Log.h"
#include "Camera.h"
#include "Game.h"

Log PlayScene::Logger(typeid(PlayScene).name());
const std::string PlayScene::SCENE_ID = "PLAY_SCENE";

void PlayScene::update() {
    m_pLevel->update();
    m_pCamera->update();
}

void PlayScene::draw() {
    m_pLevel->draw();
}

void PlayScene::onActivate() {
    Logger.debug("Play activated");

    // TODO: level is not set because of GameScene base class
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

bool PlayScene::onDeactivate() {
    Logger.debug("Play deactivated");
    return false;
}

std::string PlayScene::getSceneId() const {
    return SCENE_ID;
}
