#include "RotationModifier.h"

RotationModifier::RotationModifier(void)
{
}


RotationModifier::~RotationModifier(void)
{
}

void RotationModifier::Update(ParticleCollection* c, float delta)
{
	for (int i = 0; i < c->Count(); i++)
    {
		Particle* p = c->Particles[i];
		p->Rotation += p->AngularVelocity * delta;
		c->Particles[i] = p;
    }
}
