#include "pch.h"
#include "PlayScene.h"
#include "Log.h"
#include "Camera.h"
#include "Game.h"

Log PlayScene::Logger(typeid(PlayScene).name());
const std::string PlayScene::SCENE_ID = "PLAY_SCENE";
const std::string PlayScene::PLAYER_TYPE = "player";
const std::string PlayScene::LEVEL_TYPE = "level";

void PlayScene::update() {
    m_pLevel->update();
    m_pCamera->update();
}

void PlayScene::draw() {
    m_pLevel->draw();
}

void PlayScene::onActivate() {
    if (m_drawables.find(PLAYER_TYPE) == m_drawables.end()) {
        Logger.error("No player object in scene " + SCENE_ID);
        return;
    }
    if (m_drawables.find(LEVEL_TYPE) == m_drawables.end()) {
        Logger.error("No level object in scene " + SCENE_ID);
        return;
    }

    m_pPlayer = std::dynamic_pointer_cast<Player>(m_drawables[PLAYER_TYPE]);
    m_pLevel = std::dynamic_pointer_cast<Level>(m_drawables[LEVEL_TYPE]);

    m_pLevel->setPlayer(m_pPlayer);
    m_pCamera = std::make_unique<Camera>(
        Game::instance().getWindowWidth(),
        Game::instance().getWindowHeight(),
        m_pLevel->getWidthPx(),
        m_pLevel->getHeightPx(),
        m_pPlayer
    );

    Logger.debug("Play activated");
}

bool PlayScene::onDeactivate() {
    Logger.debug("Play deactivated");
    return false;
}

std::string PlayScene::getSceneId() const {
    return SCENE_ID;
}
