#pragma once
#include "ParticleCollection.h"

struct Modifier
{
public:
	Modifier(void);
	~Modifier(void);

	virtual void Update(ParticleCollection* collection, float elapsedTime);
};

