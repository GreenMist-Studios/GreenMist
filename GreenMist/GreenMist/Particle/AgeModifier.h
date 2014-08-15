#pragma once
#include "Modifier.h"
#include "ParticleCollection.h"

class AgeModifier : public Modifier
{
public:
	AgeModifier(float time);

	void Update(ParticleCollection* c, float delta);

private:
	float _term;
    float _totalSeconds;
};

