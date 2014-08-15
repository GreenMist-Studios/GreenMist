#pragma once
#include "../Vector2.h"
#include <SDL2/SDL.h>
#include <string>

class Particle
{
public:
	Particle(void);
	~Particle(void);

	 std::string Texture;
     float Inception;
     float Age;
     Vector2 Position;
     Vector2 Velocity;
     SDL_Color Color;
     float Scale;
     float Opacity;
     float Rotation;
	 float AngularVelocity;
     float Mass;
};

