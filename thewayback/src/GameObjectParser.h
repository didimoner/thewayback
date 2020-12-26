#pragma once
#include "vendor/tinyxml2.h"

class GameObject;

class GameObjectParser {

public:
    static std::shared_ptr<GameObject> parse(tinyxml2::XMLElement* pObjectElement);

};
