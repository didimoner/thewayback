#pragma once
#include "GameScene.h"
#include "Level.h"
#include "Player.h"
#include "GameSceneCreator.h"

class Log;

class PlayScene : public GameScene {

public:
    friend class PlaySceneCreator;

    enum EventType : uint16_t {
        CHANGE_LEVEL = 0
    };

private:
    static const std::string SCENE_ID;
    static const std::string PLAYER_TYPE;
    static Log Logger;

    std::unordered_map<std::string, std::shared_ptr<Level>> m_levels;
    std::shared_ptr<UserInterface> m_pUserInterface;
    std::shared_ptr<Level> m_pActiveLevel;
    std::shared_ptr<Player> m_pPlayer;

public:
    void update() override;
    void draw() override;

    void onEvent(uint16_t type, std::string data) override;
    void onActivate() override;
    bool onDeactivate() override;

    std::string getSceneId() const override;
    std::shared_ptr<UserInterface> getUserInterface() const;

private:
    void changeLevel(const std::string& levelId);
    void processCollisions() const;

};

class PlaySceneCreator final : public GameSceneCreator {

public:
    std::shared_ptr<GameScene> create() const override {
        return std::make_shared<PlayScene>();
    }

};