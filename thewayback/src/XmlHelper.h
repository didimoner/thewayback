#pragma once
#include "vendor/tinyxml2.h"

class Log;
class GameObject;

class XmlHelper {

private:
    static Log Logger;

public:
    static std::shared_ptr<GameObject> parseGameObject(tinyxml2::XMLElement* pObjectElement);
    static std::string getStringProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static int getIntProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static uint32_t getUnsignedProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static float getFloatProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static bool getBoolProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static tinyxml2::XMLElement* getCustomProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);

};