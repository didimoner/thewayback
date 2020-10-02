#pragma once
#include "vendor/tinyxml2.h"

class Log;
class Level;
struct Tileset;

class LevelParser {

private:
    static Log Logger;

public:
    static std::shared_ptr<Level> parse(const std::string& filename);

private:
    static void parseMapProps(tinyxml2::XMLElement* pPropsRoot);
    static void parseTilesets(tinyxml2::XMLElement* pTilesetsRoot, Level& level);
    static void parseTileLayers(tinyxml2::XMLElement* pLayerRoot, std::shared_ptr<Level>& pLevel);
    static void parseObjectLayers(tinyxml2::XMLElement* pObjectsRoot, Level& level);
    static void parseObstacles(tinyxml2::XMLElement* pRoot, Level& level);
    static void parseGameObjects(tinyxml2::XMLElement* pRoot, Level& level);

    static std::string getStringProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static int getIntProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static float getFloatProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static bool getBoolProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);

    static tinyxml2::XMLElement* getCustomProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
};