#include "AlphaModifier.h"

AlphaModifier::AlphaModifier()
{
    //ctor
}

AlphaModifier::~AlphaModifier()
{
    //dtor
}

void AlphaModifier::Update(ParticleCollection* c, float delta)
{
      for (int i = 0; i < c->Count(); i++)
      {
		  Particle* p = c->Particles[i];
          p->Opacity = MathExtender::Clamp(1.0f - p->Age,1.0f,0.0f);
          c->Particles[i] = p;
      }
}
