#pragma once
#include "GameObject.h"
#include "Log.h"
#include "tinyxml2.h"

class StateParser {

private:
    static Log* Logger;

public:
    bool parse(std::string filename, std::string stateId, std::vector<GameObject*> &gameObjects);

private:
    void parseTextures(tinyxml2::XMLElement* pTexturesRoot);
    void parseObjects(tinyxml2::XMLElement* pObjectsRoot, std::vector<GameObject*> &gameObjects);

};