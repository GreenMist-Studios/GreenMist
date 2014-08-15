#pragma once
#include "GMTimer.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

#define CColor(r,g,b) SDL_Color {r,g,b}

#include "Settings.h"

class GMApplication
{
public:
	GMApplication(void);
	~GMApplication(void);

    bool Initialize(std::string title, int width, int height);

	virtual void LoadContent();
	virtual void Update(float delta);
	virtual void HandleEvent(SDL_Event e);
	virtual void Draw(float delta);
	void Run();

protected:
	SDL_Window* Window;
	std::string Title;

	SDL_Renderer* Renderer;
	GMTimer MainTimer;
	GMTimer FrameTimer;
    int FPS;
	bool Debug;
private:
    int framecount;
    GMTimer fps;
};

