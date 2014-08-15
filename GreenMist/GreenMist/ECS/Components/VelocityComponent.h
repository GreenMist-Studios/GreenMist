#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include "../Component.h"


class VelocityComponent : public Component
{
    public:
        VelocityComponent() {vX = 0; vY = 0;}
        VelocityComponent(float x, float y) {vX = x; vY = y;}

        float vX;
        float vY;
};

#endif // VELOCITYCOMPONENT_H
