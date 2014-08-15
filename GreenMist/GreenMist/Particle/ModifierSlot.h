#pragma once
#include "Modifier.h"

class ModifierSlot
{
public:
	ModifierSlot(void);
	ModifierSlot(Modifier* modifier, float frequency = 60.0f);
	~ModifierSlot(void);

	void Update(ParticleCollection* collection, float elapsedSeconds);

	Modifier* MainModifier;
	float Frequency;

private:
	float secondsSinceLastUpdate;
};

