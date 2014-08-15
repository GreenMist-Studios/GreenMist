#pragma once

#include <vector>
#include "Modifier.h"
#include "ModifierSlot.h"

class ModifierCollection
{
public:
	ModifierCollection(void);
	~ModifierCollection(void);

	void Add(Modifier* modifier, float frequency = 60);

	std::vector<ModifierSlot> Slots;
};

