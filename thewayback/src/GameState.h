#pragma once
#include "pch.h"

class GameState {

public:
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void onActivate() = 0;
    virtual bool onDeactivate() = 0;

    virtual std::string getStateId() const = 0;

};