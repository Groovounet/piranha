/***********************************************\
	GTL sample : frustum culling
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	main.cpp, 02/10/2004
\***********************************************/

#include "./sample.h"
#include "./window_sdl.h"

int main (int argc, char* argv[])
{
	if (!CWindowSDL::Instance ()->Create (
		WINDOW_NAME, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT, 
		WINDOW_COLOR, 
		false))
		return 1;

	if (!Begin ())
		return 1;

	bool bExit = false;
    while (!bExit)
    {
		SDL_Event Event;
		while (SDL_PollEvent (&Event))
		{
			switch (Event.type)
			{
			case SDL_QUIT:
				bExit = true;
				break;

			case SDL_KEYDOWN:
				KeyboardDown (Event.key.keysym.sym);
				break;

			case SDL_KEYUP:
				KeyboardUp (Event.key.keysym.sym);
				break;

			default:
				break;
            }
		}

		Draw ();

		CWindowSDL::Instance ()->Swap ();
	}

    End ();
	CWindowSDL::Kill ();

	return 0;
}


