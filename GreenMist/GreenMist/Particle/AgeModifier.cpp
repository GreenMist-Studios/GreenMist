#include "AgeModifier.h"

AgeModifier::AgeModifier(float term)
{
	_term = term;
	_totalSeconds = 0;
}

void AgeModifier::Update(ParticleCollection* c, float delta)
{
	 _totalSeconds += delta;

      for (int i = 0; i < c->Count(); i++)
      {
		  Particle* p = c->Particles[i];
          p->Age = (_totalSeconds - p->Inception) / _term;
          c->Particles[i] = p;
      }
}
