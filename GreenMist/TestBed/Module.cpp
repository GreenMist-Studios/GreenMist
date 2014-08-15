#include "Module.h"

Module::Module()
{
}

Module::Module(std::string _str, SDL_Renderer* render)
{
    //tmxMap = new TMXMap();
    //tmxMap->Load(render, _str);
    renderer = render;
}

Module::~Module()
{
    //dtor
}

void Module::Update(float delta)
{

}

void Module::Draw()
{/*
    for (int i = 0; i < tmxMap->TileLayers.size(); i++)
    {
        TMXTileLayer* tlayer = tmxMap->TileLayers[i];
        for (int num = 0; num < tlayer->Tiles.size(); num++)
        {
            TMXTileset* tileset = tmxMap->Tilesets[ tlayer->Tiles[num]->GetTilesetIndex()];
            int gid = tlayer->Tiles[num]->GetGid();
            Vector2 position = tlayer->Tiles[num]->GetPosition();
            SDL_Rect sourceRect = tileset->GidRectangles[gid];

            tileset->GetTexture()->render(position.X,position.Y, &sourceRect, 0, NULL);
        }
    }
    if (Settings::Debug)
    {
        for (int i = 0; i < tmxMap->ObjectGroupLayers.size(); i++)
        {
            for (int num = 0; num < tmxMap->ObjectGroupLayers[i]->Objects.size(); num++)
            {
                if (tmxMap->ObjectGroupLayers[i]->Objects[num]->ObjectType == Rectangle)
                {
                    rectangleRGBA(renderer, tmxMap->ObjectGroupLayers[i]->Objects[num]->GetPosition().X,
                                  tmxMap->ObjectGroupLayers[i]->Objects[num]->GetPosition().Y,
                                  tmxMap->ObjectGroupLayers[i]->Objects[num]->GetPosition().X + tmxMap->ObjectGroupLayers[i]->Objects[num]->GetWidth(),
                                  tmxMap->ObjectGroupLayers[i]->Objects[num]->GetPosition().Y + tmxMap->ObjectGroupLayers[i]->Objects[num]->GetHeight(),
                                  255,255,0,255
                                  );
                }
            }
        }
    }*/
}

int Module::GetHeight()
{
    return h;
}
int Module::GetWidth()
{
    return w;
}
