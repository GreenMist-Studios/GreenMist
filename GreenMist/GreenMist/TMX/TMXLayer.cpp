#include "TMXLayer.h"
TMXLayer::TMXLayer()
{

}
TMXLayer::TMXLayer(std::string n, int wTiles, int hTiles, int o)
{
    //ctor
    name = n;
    widthInTiles = wTiles;
    heightInTiles = hTiles;
    opacity = o;
}

TMXLayer::~TMXLayer()
{
    //dtor
}
