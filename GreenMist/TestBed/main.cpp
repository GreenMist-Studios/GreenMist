#include "TestBedApp.h"

#include <stdio.h>
#include <string>
#include <vector>

TestBedApp* App = NULL;

int main( int argc, char* args[] )
{
	App = new TestBedApp();
	App->Initialize("TestBed", 1280,720);

	App->LoadContent();

	App->Run();

	return 0;
}
