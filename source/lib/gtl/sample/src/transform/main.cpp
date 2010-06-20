/***********************************************\
	GTL sample
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	main.cpp, 03/10/2004
\***********************************************/

#include "./sample.h"

int main (int argc, char* argv[])
{
	if (!CWindowSDL::Instance ()->Create (
		WINDOW_NAME, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT, 
		WINDOW_COLOR, 
		false))
		return 1;

	if (!Init ())
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
				if (Event.key.keysym.sym == SDLK_ESCAPE)
					bExit = true;
				else if (Event.key.keysym.sym == SDLK_F1)
					g_uiTransformMode = 0;
				else if (Event.key.keysym.sym == SDLK_F2)
					g_uiTransformMode = 1;
				else if (Event.key.keysym.sym == SDLK_F3)
					g_uiTransformMode = 2;
				break;
			default:
				break;
            }
		}

		Draw ();

		CWindowSDL::Instance ()->Swap ();
	}

	CWindowSDL::Kill ();
	End ();

	return 0;
}
