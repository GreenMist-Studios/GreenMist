#ifndef MODULE_H
#define MODULE_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include "TMX/TMXMap.h"
#include "TMX/TMXTileLayer.h"
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Settings.h"

class Module
{
    public:
        Module();
        Module(std::string str, SDL_Renderer* renderer);
        virtual ~Module();
        void Update(float delta);
        void Draw();
        int GetHeight();
        int GetWidth();

        TMXMap* tmxMap;
        b2Body* collisionBody;
    private:
        int h;
        int w;
        std::string str;
        SDL_Renderer* renderer;
};

#endif // MODULE_H
