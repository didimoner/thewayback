#pragma once
#include "tinyxml2.h"

class Level;
struct Tileset;
class Log;

using namespace tinyxml2;

class LevelParser {

private:
    static Log* Logger;

public:
    Level* parse(std::string filename);
    
private:
    void parseMapProps(XMLElement* pPropsRoot);
    void parseTilesets(XMLElement* pTilesetsRoot, std::vector<Tileset>* pTilesets);
    void parseTileLayers(XMLElement* pLayerRoot, Level* pLevel);
    void parseObjectLayers(XMLElement* pObjectsRoot, Level* pLevel);
    void parseCollidables(XMLElement* pRoot, Level* pLevel);
    void parseGameObjects(XMLElement* pRoot, Level* pLevel);

    std::string getStringProperty(XMLElement* pElementRoot, std::string name) const;
};