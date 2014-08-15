#ifndef TMXMAP_H
#define TMXMAP_H

#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <stdio.h>
#include <assert.h>
#include <stdexcept>
#include <sstream>
#include <map>
#include <vector>
#include <zlib/zlib.h>
#include <string>
#include "tinyxml2.h"
#include "TMXTileset.h"
#include "TMXLayer.h"
#include "TMXTileLayer.h"
#include "TMXObjectGroupLayer.h"
#include "../MathExtender.h"

using namespace tinyxml2;


class TMXMap
{
    public:
        TMXMap();
        virtual ~TMXMap();

        bool Load(SDL_Renderer* renderer, std::string directory);

        std::map<std::string, std::string> Properties;
        std::vector<TMXLayer*> Layers;
        std::vector<TMXTileLayer*> TileLayers;
        std::vector<TMXObjectGroupLayer*> ObjectGroupLayers;
        std::vector<TMXTileset*> Tilesets;
    private:
        std::string Version;
        std::string Orientation;
        int WidthInTiles;
        int HeightInTiles;
        int TileWidth;
        int TileHeight;

};

#endif // TMXMAP_H
