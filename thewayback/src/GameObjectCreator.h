#pragma once
#include "GameObject.h"

class GameObjectCreator {
        
public:
    virtual ~GameObjectCreator() {}
    virtual GameObject* create() const = 0;

};

