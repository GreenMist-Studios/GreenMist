#ifndef TMXOBJECTGROUPLAYER_H
#define TMXOBJECTGROUPLAYER_H

#include <string>
#include <vector>
#include "TMXLayer.h"
#include "../Vector2.h"
#include <SDL2/SDL.h>


enum ObjectTypes { Ellipse, Rectangle, PolyLine, Polygon, TileType};

class Object
{
public:
    Object();
    Object(Vector2 pos, int w, int h) {
        position = pos;
        width = w;
        height = h;
    }

    Vector2 GetPosition(){return position;}
    int GetGid() {return gid;}
    int GetWidth() { return width; }
    int GetHeight() { return height; }
    void SetGid(int _gid) { gid=_gid;}

    ObjectTypes ObjectType;
    std::vector<Vector2> Points;
    std::string Type;
private:
    int gid;
    Vector2 position;
    int width;
    int height;
};

class TMXObjectGroupLayer : public TMXLayer
{
    public:
        TMXObjectGroupLayer(std::string name, int wTiles, int hTiles, int o) : TMXLayer(name,wTiles,hTiles,o){}
        virtual ~TMXObjectGroupLayer(){}

        std::vector<Object*> Objects;
        SDL_Color Color;
};

#endif // TMXOBJECTGROUPLAYER_H

