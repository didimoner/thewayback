#pragma once
#include "GameState.h"
#include "Log.h"

class PlayState : public GameState {

private:
    static const std::string s_stateId;
    static Log* Logger;

public:
    virtual void update();
    virtual void draw();

    virtual void onActivate();
    virtual bool onDeactivate();

    virtual std::string getStateId() const {
        return s_stateId;
    }

};

