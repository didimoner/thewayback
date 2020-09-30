#pragma once
#include "vendor/tinyxml2.h"

class Log;
class GameObject;

class StateParser {

private:
    static Log Logger;

public:
    bool parse(std::string filename, std::string stateId, std::vector<GameObject*>& gameObjects);

private:
    static void parseTextures(tinyxml2::XMLElement* pTexturesRoot);
    static void parseObjects(tinyxml2::XMLElement* pObjectsRoot, std::vector<GameObject*>& gameObjects);

};
