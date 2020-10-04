#pragma once
#include "pch.h"
#include "GameState.h"

class GameStateCreator {

public:
    virtual ~GameStateCreator() = default;
    virtual std::unique_ptr<GameState> create() const = 0;

};