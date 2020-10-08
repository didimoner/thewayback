#pragma once
#include "vendor/tinyxml2.h"

class Log;
class GameScene;
class GameObject;

class GameSceneParser {

private:
    static Log Logger;

public:
    static std::unique_ptr<GameScene> parse(const std::string& filename);

private:
    static void parseObjects(tinyxml2::XMLElement* pObjectsRoot, GameScene& gameScene);

};
