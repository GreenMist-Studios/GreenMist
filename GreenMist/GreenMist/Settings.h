#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <SDL2/SDL.h>

struct Settings
{
public:
    static bool Debug;
    static bool VSync;

};

inline void GMEnableDebug()
{
    Settings::Debug = true;
}

inline void GMDisableDebug()
{
    Settings::Debug = false;
}

inline void GMEnableVSync()
{
    Settings::VSync = true;

		//Enable VSync
		if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
		{
			printf( "Warning: VSync not enabled!" );
		}
}

inline void GMDisableVSync()
{
    Settings::VSync = false;

		//Enable VSync
		if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "0" ) )
		{
			printf( "Warning: VSync not enabled!" );
		}
}


#endif
