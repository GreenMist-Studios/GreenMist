#include "MoveModifier.h"


MoveModifier::MoveModifier(void)
{
}


MoveModifier::~MoveModifier(void)
{
}

void MoveModifier::Update(ParticleCollection* c, float delta)
{
	for (int i = 0; i < c->Count(); i++)
    {
		Particle* p = c->Particles[i];
		p->Position += p->Velocity * delta;
		 c->Particles[i] = p;
    }
}
