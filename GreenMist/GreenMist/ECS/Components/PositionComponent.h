#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "../Component.h"


class PositionComponent : public Component
{
    public:
        PositionComponent() { x = 0; y=0;}
        PositionComponent(float xx, float yy) { x = xx; y = yy;}

        float x;
        float y;
};

#endif // POSITIONCOMPONENT_H
