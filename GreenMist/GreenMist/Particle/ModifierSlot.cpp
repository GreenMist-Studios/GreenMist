#include "ModifierSlot.h"


ModifierSlot::ModifierSlot(void)
{
	Frequency = 60;
	secondsSinceLastUpdate = 0;
}

ModifierSlot::ModifierSlot(Modifier* m, float freq)
{
	MainModifier = m;
	Frequency = freq;
	secondsSinceLastUpdate = 0;
}

ModifierSlot::~ModifierSlot(void)
{
}

void ModifierSlot::Update(ParticleCollection* collection, float delta)
{
	secondsSinceLastUpdate += delta;

    if (secondsSinceLastUpdate >= (1.0f / Frequency))
    {
         MainModifier->Update(collection, secondsSinceLastUpdate);
         secondsSinceLastUpdate = 0.0f;
    }
}
