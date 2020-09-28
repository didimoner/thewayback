#pragma once

class GameObject;

class GameObjectCreator {
        
public:
    virtual GameObject* create() const = 0;

};