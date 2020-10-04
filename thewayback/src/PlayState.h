#pragma once
#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include "GameStateCreator.h"

class Log;

class PlayState : public GameState {

private:
    friend class PlayStateCreator;
    PlayState() = default;

    static const std::string STATE_ID;
    static Log Logger;

    std::shared_ptr<Level> m_pLevel;
    std::shared_ptr<Player> m_pPlayer;

public:
    void update() override;
    void draw() override;

    void onActivate() override;
    bool onDeactivate() override;

    std::string getStateId() const override;

};

class PlayStateCreator final : public GameStateCreator {

public:
    std::unique_ptr<GameState> create() const override {
        return std::unique_ptr<PlayState>(new PlayState);
    }

};