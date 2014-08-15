#pragma once
#include <SDL2/SDL.h>
#include "../Component.h"
#include "../../Particle/Profile.h"
#include "../../Particle/ParticleCollection.h"
#include "../../Particle/ModifierCollection.h"
#include "../../Particle/EmitterParameter.h"
#include "RenderOrderComponent.h"
#include <string>

class EmitterComponent :
	public Component
{
public:
	EmitterComponent()
	{
		BlendMode = SDL_BLENDMODE_BLEND;
		ReclaimInterval = 0;
		totalSeconds = 0;
		lifeSpan = 2;
		secondsSinceLastReclaim = 0;

		Collection = new ParticleCollection(20);
		Modifiers = new ModifierCollection();
		Parameters = new EmitterParameter();
	}

	EmitterComponent(std::string texture, int capacity, float lifespan, Profile* profile, EmitterParameter* param)
	{
		BlendMode = SDL_BLENDMODE_BLEND;
		Texture = texture;
		lifeSpan = lifespan;
		Collection = new ParticleCollection(capacity);
		Modifiers = new ModifierCollection();
		Parameters = param;
		ProfileType = profile;

		totalSeconds = 0;
		secondsSinceLastReclaim = 0;
		ReclaimInterval = 0;
	}

	~EmitterComponent()
	{
		ReclaimInterval = 0;
		totalSeconds = 0;
		lifeSpan = 2;
		secondsSinceLastReclaim = 0;
		Collection = NULL;
		Modifiers = NULL;
		Parameters = NULL;
	}

	ParticleCollection* Collection;
	ModifierCollection* Modifiers;
	Profile* ProfileType;
	EmitterParameter* Parameters;
	float ReclaimInterval;
	SDL_BlendMode BlendMode;

	float secondsSinceLastReclaim;
    float totalSeconds;
    float lifeSpan;
	std::string Texture;

	void ReclaimParticles()
	{
		for (int i = 0; i < Collection->Count(); i++)
		{
			if (totalSeconds - Collection->Particles[i]->Inception > lifeSpan)
			{
				// delete Collection->Particles[i];
				Collection->Particles.erase(Collection->Particles.begin()+i);
				i--;
			}
		}
	}

	void Trigger(Vector2 position)
	{
		int numToRelease = MathExtender::Random(Parameters->Quantity);
        int count = Collection->Release(numToRelease);

            Particle* p = new Particle();
			p->Texture = Texture;
            for (int i = 0 ; i < count; i++)
            {
				Vector2 offset = Vector2::Zero;
				Vector2 heading = Vector2::Zero;
				ProfileType->GetOffsetAndHeading(offset, heading);

                p->Position = offset;
                p->Velocity = heading;


                p->Age = 0.0f;
                p->Inception = totalSeconds;

				p->Position += position;

                float speed = MathExtender::Random(Parameters->Speed);

                p->Velocity.X *= speed;
                p->Velocity.Y *= speed;

				p->Color = MathExtender::Random(Parameters->Color);

                p->Opacity = MathExtender::Random(Parameters->Opacity);
                p->Scale = MathExtender::Random(Parameters->Scale);
                p->Rotation = MathExtender::Random(Parameters->Rotation);
				p->AngularVelocity = MathExtender::Random(Parameters->AngularVelocity);
                p->Mass = MathExtender::Random(Parameters->Mass);

				Collection->Particles.push_back(p);
     }
}
};

