#ifndef TILES_H
#define TILES_H

#include <vector>
#include "StaticTile.h"

class Tiles
{
    public:
        Tiles(int w, int h);
        virtual ~Tiles();
        void Initialize();

        int GetTileWidth();
        int GetTileHeight();

        std::vector<StaticTile*> TileList;

    private:
        int tileWidth;
        int tileHeight;
};

#endif // TILES_H
