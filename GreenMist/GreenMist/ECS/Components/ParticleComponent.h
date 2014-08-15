#ifndef PARTICLECOMPONENT_H
#define PARTICLECOMPONENT_H

#include <ECS/Component.h>
#include <string>

class ParticleComponent : Component
{
    public:
        ParticleComponent() {}

		string Texture;
        float Inception;
        float Age;
        Vector2 Position;
        Vector2 Velocity;
        SDL_Color Color;
        float Scale;
        float Opacity;
        float Rotation;
        float Mass;
};

#endif // PARTICLECOMPONENT_H
