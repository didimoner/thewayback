#include "pch.h"
#include "PlayScene.h"
#include "Log.h"
#include "Camera.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "Collision.h"
#include "ECollisionType.h"
#include "SolidObject.h"
#include "Portal.h"
#include "SoundPlayer.h"
#include "TextBox.h"
#include "FontManager.h"

Log PlayScene::Logger(typeid(PlayScene).name());
const std::string PlayScene::SCENE_ID = "PLAY_SCENE";
const std::string PlayScene::PLAYER_TYPE = "player";

void PlayScene::update() {
    m_pPlayer->update();
    m_pActiveLevel->update();
    processCollisions();
    m_pCamera->update();

    if (InputHandler::instance().isKeyPressed(SDL_SCANCODE_P)) {
        SoundPlayer::playSound("ding");
    }

    if (InputHandler::instance().isKeyPressed(SDL_SCANCODE_O)) {
        SoundPlayer::playSound("collect");
    }

    m_text->update();
}

void PlayScene::draw() {
    m_pActiveLevel->draw();
    m_pPlayer->draw();
    m_text->draw();
}

void PlayScene::onEvent(uint16_t type, std::string data) {
    switch (type) {
        case EventType::CHANGE_LEVEL:
            changeLevel(data);
            break;
    }
}

void PlayScene::onActivate() {
    if (m_sceneObjects.find(PLAYER_TYPE) == m_sceneObjects.end()) {
        Logger.error("No player object in scene " + SCENE_ID);
        return;
    }

    m_pPlayer = std::dynamic_pointer_cast<Player>(m_sceneObjects[PLAYER_TYPE]);
    m_pCamera = std::make_unique<Camera>(
        Game::instance().getWindowWidth(),
        Game::instance().getWindowHeight(),
        0, 0, m_pPlayer
    );
    changeLevel(m_sceneProps.stringVal("defaultLevel"));

    m_sceneObjects.clear();

    //SoundPlayer::playMusic("main_theme", -1);

    std::string fontId = "pixel";
    int32_t fontSize = 24;
    FontManager::instance().loadFont("pixel.ttf", fontId, fontSize);
    m_text = std::make_shared<TextBox>(fontId);

    GameObject::InitParams initParams;
    initParams.x = 200;
    initParams.y = 32;
    initParams.width = 480;
    initParams.height = fontSize * 2;
    initParams.zIndex = 200;
    m_text->init(initParams);

    std::wstring wstring = L"Привет, Мир! Это мое первое сообщение в виде текста для этой игры. Надеюсь, что оно понравится вам!";
    m_text->setText(wstring);

    Logger.debug("Play activated");
}

bool PlayScene::onDeactivate() {
    Logger.debug("Play deactivated");
    return false;
}

std::string PlayScene::getSceneId() const {
    return SCENE_ID;
}

void PlayScene::changeLevel(const std::string& levelId) {
    if (m_levels.find(levelId) == m_levels.end()) {
        m_levels.emplace(levelId, LevelParser::parse(levelId));
    }

    const auto pLevel = m_levels[levelId];
    m_pActiveLevel = pLevel;
    m_pCamera->setLevelSize(m_pActiveLevel->getWidthPx(), m_pActiveLevel->getHeightPx());

    Logger.debug("Level changed to " + levelId);
}

void PlayScene::processCollisions() const {
    auto solidObjects = m_pActiveLevel->getObjectsNearby(m_pPlayer->getCollider());
    ECollisionType collisionType;
    for (const auto& pObject : solidObjects) {
        if (pObject->getType() == "portal") {
            collisionType = ECollisionType::PLAYER_PORTAL;
        } else {
            collisionType = ECollisionType::PLAYER_OBSTACLE;
        }

        Collision::checkCollidables(collisionType, m_pPlayer, pObject);
    }
}
