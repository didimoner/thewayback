#pragma once
#include "GameScene.h"
#include "Level.h"
#include "Player.h"
#include "GameSceneCreator.h"
#include "TextBox.h"

class Log;

class PlayScene : public GameScene {

public:
    enum EventType : uint16_t {
        CHANGE_LEVEL = 0
    };

private:
    friend class PlaySceneCreator;
    PlayScene() = default;

    static const std::string SCENE_ID;
    static const std::string PLAYER_TYPE;
    static Log Logger;

    std::unordered_map<std::string, std::shared_ptr<Level>> m_levels;
    std::shared_ptr<Level> m_pActiveLevel;
    std::shared_ptr<Player> m_pPlayer;
    std::shared_ptr<TextBox> m_text;

public:
    void update() override;
    void draw() override;

    void onEvent(uint16_t type, std::string data) override;
    void onActivate() override;
    bool onDeactivate() override;

    std::string getSceneId() const override;

private:
    void changeLevel(const std::string& levelId);
    void processCollisions() const;

};

class PlaySceneCreator final : public GameSceneCreator {

public:
    std::unique_ptr<GameScene> create() const override {
        return std::unique_ptr<PlayScene>(new PlayScene);
    }

};