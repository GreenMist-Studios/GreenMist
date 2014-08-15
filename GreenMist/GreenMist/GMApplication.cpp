#include "GMApplication.h"


GMApplication::GMApplication(void)
{
	Window = NULL;
	Renderer = NULL;
	framecount = 0;
}


GMApplication::~GMApplication(void)
{
	//Destroy window
	SDL_DestroyRenderer( Renderer );
	SDL_DestroyWindow( Window );

	Window = NULL;
	Renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool GMApplication::Initialize(std::string title, int width, int height)
{
	MainTimer.start();

	bool success = false;
	Title = title;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

        //int ret = SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &Window, &Renderer);
        //SDL_SetWindowTitle(Window, title.c_str());
		//Create window
		Window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
		if( Window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
            //Create renderer for ow
			Renderer = SDL_CreateRenderer( Window, -1, SDL_RENDERER_ACCELERATED );
			if( Renderer == NULL)
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( Renderer, 0x00, 0x00, 0x00, 0xff);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

                SDL_RenderClear( Renderer );
			}
		}
	}

	return success;
}

void GMApplication::Run()
{
	bool quit = false;
	SDL_Event e;

	FrameTimer.start();
	int oldticks = 0;
    fps.start();
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			HandleEvent(e);
		}

		int tick = FrameTimer.getTicks();
		Update((float)(tick - oldticks)/1000.f);

		SDL_SetRenderDrawColor( Renderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderClear( Renderer );
		Draw((float)(tick - oldticks)/1000.f);
		SDL_RenderPresent( Renderer );

        framecount++;

        if (fps.getTicks() > 1000)
        {
            int FPS = framecount / (tick/1000.f);

            if (Settings::Debug)
            {
                std::stringstream _fpstitle;
                _fpstitle << Title << " FPS: " << FPS;
                SDL_SetWindowTitle(Window,_fpstitle.str().c_str());
            }
            else
                SDL_SetWindowTitle(Window, Title.c_str());


            fps.start();
        }

        oldticks = tick;
	}
}

void GMApplication::LoadContent()
{
}


void GMApplication::HandleEvent(SDL_Event e)
{
}

void GMApplication::Update(float delta)
{
}

void GMApplication::Draw(float delta)
{
}
