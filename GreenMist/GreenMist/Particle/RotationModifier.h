#pragma once
#include "Modifier.h"
#include "ParticleCollection.h"

class RotationModifier :
	public Modifier
{
public:
	RotationModifier(void);
	~RotationModifier(void);

	void Update(ParticleCollection* c, float delta);
};