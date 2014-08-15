#pragma once
#include "Modifier.h"

class MoveModifier :
	public Modifier
{
public:
	MoveModifier(void);
	~MoveModifier(void);

	void Update(ParticleCollection* c, float delta);
};

