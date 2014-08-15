#ifndef LEVEL_H
#define LEVEL_H

 #include <Box2D/Box2D.h>
#include <vector>
#include <stdio.h>
#include "TMX/TMXObjectGroupLayer.h"
#include "B2DDebugDraw.h"
#include "Module.h"

class Level
{
    public:
        Level();
        virtual ~Level();
        void AddModule(Module* module);
        void Draw();
        void DebugDraw();

        std::vector<Module*> Modules;
        b2World* world;
    private:

};

#endif // LEVEL_H
