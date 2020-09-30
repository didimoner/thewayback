#pragma once
#include "vendor/tinyxml2.h"

class Log;
class Level;
struct Tileset;

class LevelParser {

private:
    static Log Logger;

public:
    static Level* parse(const std::string& filename);

private:
    static void parseMapProps(tinyxml2::XMLElement* pPropsRoot);
    static void parseTilesets(tinyxml2::XMLElement* pTilesetsRoot, std::vector<Tileset>* pTilesets);
    static void parseTileLayers(tinyxml2::XMLElement* pLayerRoot, Level* pLevel);
    static void parseObjectLayers(tinyxml2::XMLElement* pObjectsRoot, Level* pLevel);
    static void parseObstacles(tinyxml2::XMLElement* pRoot, Level* pLevel);
    static void parseGameObjects(tinyxml2::XMLElement* pRoot, Level* pLevel);

    static std::string getStringProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static int getIntProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static float getFloatProperty(tinyxml2::XMLElement* pElementRoot, const std::string& name);
    static bool getBoolProperty(tinyxml2::XMLElement* pElementRoot, std::string name);

};
