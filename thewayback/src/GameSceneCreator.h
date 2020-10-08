#pragma once
#include "pch.h"
#include "GameScene.h"

class GameSceneCreator {

public:
    virtual ~GameSceneCreator() = default;
    virtual std::unique_ptr<GameScene> create() const = 0;

};