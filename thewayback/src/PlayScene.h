#pragma once
#include "GameScene.h"
#include "Level.h"
#include "Player.h"
#include "GameSceneCreator.h"

class Log;

class PlayScene : public GameScene {

private:
    friend class PlaySceneCreator;
    PlayScene() = default;

    static const std::string SCENE_ID;
    static const std::string PLAYER_TYPE;
    static const std::string LEVEL_TYPE;
    static Log Logger;

    std::shared_ptr<Level> m_pLevel;
    std::shared_ptr<Player> m_pPlayer;

public:
    void update() override;
    void draw() override;

    void onActivate() override;
    bool onDeactivate() override;

    std::string getSceneId() const override;

};

class PlaySceneCreator final : public GameSceneCreator {

public:
    std::unique_ptr<GameScene> create() const override {
        return std::unique_ptr<PlayScene>(new PlayScene);
    }

};