#pragma once
#include <GMApplication.h>
#include <Texture.h>

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include <Particle/RotationModifier.h>
#include <Particle/MoveModifier.h>
#include <Particle/AgeModifier.h>
#include <Particle/AlphaModifier.h>
#include <ECS/Components/EmitterComponent.h>
#include <ECS/Components/VelocityComponent.h>
#include <ECS/Components/PhysicsComponent.h>
#include <ECS/Systems/ParticleEntitySystem.h>
#include <ECS/Systems/PhysicsEntitySystem.h>
#include <Physics/PhysicsFactory.h>
#include <ECS/World.h>
#include "Module.h"
#include "TMX/TMXMap.h"
#include "Settings.h"
#include "Level.h"
#include "B2DDebugDraw.h"
#include "Systems/BasicRenderSystem.h"
#include "Systems/RenderOrderSystem.h"
#include <TextureManager.h>

class TestBedApp : public GMApplication
{
public:
	TestBedApp();
	~TestBedApp();

	void LoadContent();
	void Update(float delta);
	void HandleEvent(SDL_Event e);
	void Draw(float delta);

private:
    Level* l;
	Module* module;
	World* world;
	RenderOrderSystem* renderSystem;
	EmitterComponent* ec;
	PhysicsComponent* pc;
};

