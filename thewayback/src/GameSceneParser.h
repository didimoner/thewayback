#pragma once
#include "vendor/tinyxml2.h"

class Log;
class GameScene;
class GameObject;

class GameSceneParser {

private:
    static Log Logger;

public:
    static std::shared_ptr<GameScene> parse(const std::string& filename);

private:
    static void parseObjects(tinyxml2::XMLElement* pObjectsRoot, GameScene& gameScene);
    static void parseSounds(tinyxml2::XMLElement* pSoundsRoot, GameScene& gameScene);
    static void parseProps(tinyxml2::XMLElement* pPropsRoot, GameScene& gameScene);

};
