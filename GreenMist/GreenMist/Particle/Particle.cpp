#include "Particle.h"

Particle::Particle(void)
{
	 Inception = 0;
     Age = 0;
	 Position = Vector2();
     Velocity = Vector2();
     Color = SDL_Color();
     Scale = 0;
     Opacity = 0;
     Rotation = 0;
     Mass = 0;
}


Particle::~Particle(void)
{
}
