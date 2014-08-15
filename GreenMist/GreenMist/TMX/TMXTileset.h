#ifndef TMXTILESET_H
#define TMXTILESET_H

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include "../Texture.h"

class TMXTileset
{
    public:
        TMXTileset();
        virtual ~TMXTileset();
        std::string GetName() { return name; }
        int GetFirstGid() { return firstgid; }
        int GetTileWidth() { return tileWidth; }
        int GetTileHeight() { return tileHeight; }
        int GetImageWidth() { return imageWidth; }
        int GetImageHeight() { return imageHeight; }
        Texture* GetTexture(){ return texture; }
        int GetLastGid() { return lastgid; }
        void Initialize(SDL_Renderer* renderer,int _firstgid, std::string _name, int _tileWidth, int _tileHeight, std::string _imageDirectory, int _imageWidth, int _imageHeight);

        std::map<int,SDL_Rect> GidRectangles;

    private:
        int firstgid;
        std::string name;
        int tileWidth;
        int tileHeight;
        std::string imageDirectory;
        int imageWidth;
        int imageHeight;

        int lastgid;
        Texture* texture;
};

#endif // TMXTILESET_H
