#include "pch.h"
#include "PlayScene.h"
#include "Log.h"
#include "Camera.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "Collision.h"
#include "ECollisionType.h"
#include "Obstacle.h"
#include "ObstacleLayer.h"
#include <thread>

Log PlayScene::Logger(typeid(PlayScene).name());
const std::string PlayScene::SCENE_ID = "PLAY_SCENE";
const std::string PlayScene::PLAYER_TYPE = "player";
const std::string PlayScene::LEVEL_TYPE = "level";

void PlayScene::update() {
    using namespace std::chrono_literals;

    if (InputHandler::instance().isKeyPressed(SDL_SCANCODE_Q)) {
        changeLevel("test6.tmx");
        std::this_thread::sleep_for(100ms);
    }
    if (InputHandler::instance().isKeyPressed(SDL_SCANCODE_W)) {
        changeLevel("test5.tmx");
        std::this_thread::sleep_for(100ms);
    }

    m_pPlayer->update();
    m_pActiveLevel->update();

    for (const auto& pObstacleLayer : m_pActiveLevel->getObstacleLayers()) {
        auto obstacles = pObstacleLayer->getObstacles(m_pPlayer->getCollider());
        for (const auto& pObstacle : obstacles) {
            Collision::checkCollidables(ECollisionType::PLAYER_OBSTACLE, *m_pPlayer, *pObstacle);
        }
    }

    m_pCamera->update();
}

void PlayScene::draw() {
    m_pActiveLevel->draw();
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
    m_pActiveLevel->setPlayer(m_pPlayer); // TODO: I don't like this
    m_pCamera->setLevelSize(m_pActiveLevel->getWidthPx(), m_pActiveLevel->getHeightPx());
}
