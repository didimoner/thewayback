#pragma once

class GameObject;

class GameObjectCreator {
        
public:
    virtual ~GameObjectCreator() {}
    virtual GameObject* create() const = 0;

};

