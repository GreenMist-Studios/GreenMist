#include "ParticleCollection.h"

ParticleCollection::ParticleCollection()
{
	Size = 0;
}

ParticleCollection::ParticleCollection(int size)
{
	Size = size;
}


ParticleCollection::~ParticleCollection(void)
{
}

int ParticleCollection::Count()
{
	return Particles.size();
}

int ParticleCollection::Available()
{
	return Size - Particles.size();
}

int ParticleCollection::Release(int num)
{
	if (this->Count() == 0 || num == 0 || this->Available() > num)
    {
        return num;
    }
	int numToRelease = std::min(num, this->Available());

    Particles.erase (Particles.begin(),Particles.begin()+numToRelease);
    /*
	for (int i = 0; i < numToRelease; i++);
	{
	     Particles[i]
		Particles.pop_back();
	}
*/
	return numToRelease;
}
