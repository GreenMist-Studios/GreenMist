#include "Tiles.h"

Tiles::Tiles(int w, int h)
{
    //ctor
    tileWidth = w;
    tileHeight = h;
}

Tiles::~Tiles()
{
    //dtor
}

void Tiles::Initialize()
{
}

int Tiles::GetTileWidth()
{
    return tileWidth;
}

int Tiles::GetTileHeight()
{
    return tileHeight;
}
