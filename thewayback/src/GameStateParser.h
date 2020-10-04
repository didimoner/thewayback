#pragma once
#include "vendor/tinyxml2.h"

class Log;
class GameState;
class GameObject;

class GameStateParser {

private:
    static Log Logger;

public:
    static std::unique_ptr<GameState> parse(const std::string& filename);

private:
    static void parseObjects(tinyxml2::XMLElement* pObjectsRoot, GameState& gameState);

};
