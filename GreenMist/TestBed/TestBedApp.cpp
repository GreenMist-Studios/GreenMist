#include "TestBedApp.h"

TestBedApp::TestBedApp()
{
	GMEnableDebug();
	GMDisableVSync();
	module = NULL;
	world = NULL;
	renderSystem = NULL;
}


TestBedApp::~TestBedApp()
{
	module = NULL;
	world = NULL;
	renderSystem = NULL;

}

void InstantiateCircle(World* world, int x, int y)
{
	Entity* e = world->CreateEntity();
	e->AddComponent(new PositionComponent(x,y));
	e->AddComponent(new RenderOrderComponent("circle", 1));
	e->AddToWorld();
}

void InstantiateBox(World* world, int x, int y)
{
	Entity* e = world->CreateEntity();
	 
	PhysicsComponent* pc = new PhysicsComponent(PhysicsFactory::CreateBasicBodyDef(x,y,MathExtender::RandomAngle(), b2_dynamicBody, e), true, PhysicsFactory::CreateRectangleFixture(64,64,1), NULL);
	e->AddComponent(pc);
	e->AddComponent(new PositionComponent(0,0));
	e->AddComponent(new RotationComponent());
	e->AddComponent(new RenderOrderComponent("square", 10));
	e->AddToWorld();
}

void TestBedApp::LoadContent()
{
	TextureManager::SetRenderer(Renderer);
	TextureManager::Add("circle", new Texture("Circle.png"));
	TextureManager::Add("square", new Texture("square.png"));
	TextureManager::Add("cloud", new Texture("particle-cloud.png"));
	
	B2DDebugDraw* DebugInstance = new B2DDebugDraw(Renderer);
	DebugInstance->SetFlags( b2Draw::e_shapeBit );

	world = new World();

	PhysicsEntitySystem* pes = world->SetSystem(new PhysicsEntitySystem(1/60.0f, Vector2(0,10), 8, 8));

	b2Body* b = pes->World->CreateBody(PhysicsFactory::CreateBasicBodyDef(640,710,0,b2_staticBody, NULL));
	b->CreateFixture(PhysicsFactory::CreateRectangleFixture(1280,20, 1));

	renderSystem = world->SetSystem(new RenderOrderSystem(), true);
	world->SetSystem(new ParticleEntitySystem(0.0f));

	world->Initialize();

	Entity* e = world->CreateEntity();

	ec = new EmitterComponent("cloud", 80, 10.0f, new RingProfile(5,false), new EmitterParameter());
	ec->Modifiers->Add(new AlphaModifier());
	ec->Modifiers->Add(new AgeModifier(0.2f));
	ec->Modifiers->Add(new MoveModifier());
	ec->Modifiers->Add(new RotationModifier());
	 
	pc = new PhysicsComponent(PhysicsFactory::CreateBasicBodyDef(1000,400,2.0f, b2_dynamicBody, e), true, PhysicsFactory::CreateRectangleFixture(64,64,1), NULL);
	e->AddComponent(ec);
	e->AddComponent(pc);
	e->AddComponent(new PositionComponent(0,0));
	e->AddComponent(new VelocityComponent(100,0));
	e->AddComponent(new RotationComponent());
	e->AddComponent(new RenderOrderComponent("square", 10));
	e->AddToWorld();
}

void TestBedApp::Update(float delta)
{
	world->SetDelta(delta);
	world->Process();
}

void TestBedApp::HandleEvent(SDL_Event e)
{

	if (e.type == SDL_KEYDOWN )
	{
		if (e.key.keysym.sym == SDLK_TAB)
			Settings::Debug = !Settings::Debug;

		if (e.key.keysym.sym == SDLK_SPACE)
		{
			InstantiateCircle(world, MathExtender::Random(0,1280), MathExtender::Random(0,720));
			InstantiateCircle(world, MathExtender::Random(0,1280), MathExtender::Random(0,720));
			printf("Num Entities: %d\n", world->GetEntityManager()->GetActiveEntityCount());
		}
		
		if (e.key.keysym.sym == SDLK_RETURN)
		{
			InstantiateBox(world, MathExtender::Random(0,1280), 0);
		}
	}

	if (e.button.button == SDL_BUTTON_LEFT)
	{
		ec->Trigger(Vector2(e.button.x, e.button.y));
	}
}

void TestBedApp::Draw(float delta)
{
	renderSystem->Process();
	if (Settings::Debug)
	pc->World->DrawDebugData();
}
