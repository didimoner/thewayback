#pragma once
#include "GameState.h"
#include "Level.h"

class Log;

class PlayState : public GameState {

private:
    static const std::string STATE_ID;
    static Log Logger;

    std::shared_ptr<Level> m_pLevel;

public:
    void update() override;
    void draw() override;

    void onActivate() override;
    bool onDeactivate() override;

    std::string getStateId() const override;

};
