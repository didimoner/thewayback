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
    virtual void update();
    virtual void draw();

    virtual void onActivate();
    virtual bool onDeactivate();

    virtual std::string getStateId() const {
        return s_stateId;
    }

};

