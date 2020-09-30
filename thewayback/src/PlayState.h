#pragma once
#include "GameState.h"

class Log;
class Level;

class PlayState : public GameState {

private:
    static const std::string STATE_ID;
    static Log Logger;

    Level* m_pLevel = nullptr;

public:
    void update() override;
    void draw() override;

    void onActivate() override;
    bool onDeactivate() override;

    std::string getStateId() const override;

};
