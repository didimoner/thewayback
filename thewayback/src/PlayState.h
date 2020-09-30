#pragma once
#include "GameState.h"

class Log;
class Level;

class PlayState : public GameState {

private:
    static const std::string s_stateId;
    static Log Logger;

    Level* m_pLevel;

public:
    void update() override;
    void draw() override;

    void onActivate() override;
    bool onDeactivate() override;

    std::string getStateId() const override;

};
