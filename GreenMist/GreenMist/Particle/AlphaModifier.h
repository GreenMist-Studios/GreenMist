#ifndef ALPHAMODIFIER_H
#define ALPHAMODIFIER_H

#include "Modifier.h"
#include "../MathExtender.h"

class AlphaModifier : public Modifier
{
    public:
	AlphaModifier(void);
	~AlphaModifier(void);

	void Update(ParticleCollection* c, float delta);
};

#endif // ALPHAMODIFIER_H
