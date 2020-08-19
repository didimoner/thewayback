#pragma once
#include "GameState.h"
#include "Log.h"
#include "GameObject.h"

class MenuState : public GameState {

private:
    static const std::string s_stateId;
    static Log* Logger;

    std::vector<GameObject*> m_gameObjects;

public:
    virtual void update();
    virtual void draw();

    virtual void onActivate();
    virtual bool onDeactivate();

    virtual std::string getStateId() const {
        return s_stateId;
    }

};

