#pragma once
#include "GameState.h"

class Log;

class SplashState : public GameState {

private:
    static const std::string s_stateId;
    static Log Logger;

public:
    virtual void update();
    virtual void draw();

    virtual void onActivate();
    virtual bool onDeactivate();

    virtual std::string getStateId() const;

};
