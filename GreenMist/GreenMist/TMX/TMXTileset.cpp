#include "TMXTileset.h"

TMXTileset::TMXTileset()
{
    //ctor
}

TMXTileset::~TMXTileset()
{
    //dtor
}

void TMXTileset::Initialize(SDL_Renderer* renderer, int _fgid, std::string _name, int _twidth, int _theight, std::string _iDir, int _iwidth, int _iheight)
{
    firstgid = _fgid;
    name = _name;
    tileWidth = _twidth;
    tileHeight = _theight;
    imageDirectory = _iDir;
    imageWidth = _iwidth;
    imageHeight = _iheight;
    lastgid = _iwidth/_twidth * _iheight/_theight;

    texture = new Texture();
    texture->renderer = renderer;
    texture->loadFromFile(imageDirectory);
}
