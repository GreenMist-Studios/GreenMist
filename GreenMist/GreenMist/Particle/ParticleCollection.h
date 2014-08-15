#pragma once

#include "Particle.h"

#include <stdio.h>
#include <vector>
#include <math.h>

class ParticleCollection
{
public:
	ParticleCollection();
	ParticleCollection(int Size);
	~ParticleCollection(void);

	int Available();
	int Count();
	int Release(int num);

	std::vector<Particle*> Particles;
	int Size;
};

