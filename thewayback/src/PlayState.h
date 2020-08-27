#pragma once
#include "GameState.h"

class Log;
class Level;

class PlayState : public GameState {

private:
    static const std::string s_stateId;
    static Log* Logger;

    Level* m_pLevel;

public:
    void update();
    void draw();

    void onActivate();
    bool onDeactivate();

    std::string getStateId() const {
        return s_stateId;
    }

};

