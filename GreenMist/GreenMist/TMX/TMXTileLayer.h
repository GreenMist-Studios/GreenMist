#ifndef TMXTILELAYER_H
#define TMXTILELAYER_H

#include <string>
#include <vector>
#include "TMXLayer.h"
#include "../Vector2.h"

class Tile
{
public:
    Tile();
    Tile(int _gid, int tsI, Vector2 pos) {
        gid = _gid;
        position = pos;
        tilesetIndex = tsI;
    }

    Vector2 GetPosition(){return position;}
    int GetGid() {return gid;}
    int GetTilesetIndex() { return tilesetIndex; }
private:
    int gid;
    Vector2 position;
    int tilesetIndex;
};

class TMXTileLayer : public TMXLayer
{
    public:
        TMXTileLayer(std::string name, int wTiles, int hTiles, int o);
        virtual ~TMXTileLayer();

        std::vector<Tile*> Tiles;
};

#endif // TMXTILELAYER_H
