#pragma once
#include "vendor/tinyxml2.h"

class Log;
class Level;

class LevelParser {

private:
    static Log Logger;

public:
    static std::shared_ptr<Level> parse(const std::string& filename);

private:
    static void parseTilesets(tinyxml2::XMLElement* pRoot, Level& level);
    static void parseTileLayers(tinyxml2::XMLElement* pRoot, const std::shared_ptr<Level>& pLevel);
    static void parseObjectLayers(tinyxml2::XMLElement* pRoot, Level& level);
    static void parseObstacles(tinyxml2::XMLElement* pObstaclesRoot, Level& level);
    static void parsePortals(tinyxml2::XMLElement* pPortalsRoot, Level& level);
    static void parseNpcs(tinyxml2::XMLElement* pNpcsRoot, Level& level);

};