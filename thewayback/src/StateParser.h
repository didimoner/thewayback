#pragma once
#include "vendor/tinyxml2.h"

class Log;
class GameObject;

using namespace tinyxml2;

class StateParser {

private:
    static Log Logger;

public:
    bool parse(std::string filename, std::string stateId, std::vector<GameObject*>& gameObjects);

private:
    void parseTextures(XMLElement* pTexturesRoot);
    void parseObjects(XMLElement* pObjectsRoot, std::vector<GameObject*>& gameObjects);

};
