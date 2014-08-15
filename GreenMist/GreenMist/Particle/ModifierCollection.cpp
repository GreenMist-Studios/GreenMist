#include "ModifierCollection.h"


ModifierCollection::ModifierCollection(void)
{
}


ModifierCollection::~ModifierCollection(void)
{
}

void ModifierCollection::Add(Modifier* m, float freq)
{
	Slots.push_back(ModifierSlot(m,freq));
}
