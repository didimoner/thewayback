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
    static void parseTilesets(tinyxml2::XMLElement* pTilesetsRoot, Level& level);
    static void parseTileLayers(tinyxml2::XMLElement* pLayerRoot, const std::shared_ptr<Level>& pLevel);
    static void parseObjectLayers(tinyxml2::XMLElement* pObjectsRoot, Level& level);
    static void parseObstacles(tinyxml2::XMLElement* pRoot, Level& level);
    static void parseGameObjects(tinyxml2::XMLElement* pRoot, Level& level);

};