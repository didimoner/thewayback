#pragma once

class GameObject;

class GameObjectCreator {

public:
    virtual ~GameObjectCreator() = default;
    virtual std::shared_ptr<GameObject> create() const = 0;

};
