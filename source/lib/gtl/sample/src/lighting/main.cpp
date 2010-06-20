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

	SDL_EnableUNICODE (0);

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
			case SDL_KEYUP:
				if (Event.key.keysym.sym == SDLK_UP || Event.key.keysym.sym == SDLK_RIGHT)
					g_bRot1 = false;
				if (Event.key.keysym.sym == SDLK_DOWN || Event.key.keysym.sym == SDLK_LEFT)
					g_bRot2 = false;
				break;
			case SDL_KEYDOWN:
				if (Event.key.keysym.sym == SDLK_ESCAPE)
					bExit = true;
				if (Event.key.keysym.sym == SDLK_UP || Event.key.keysym.sym == SDLK_RIGHT)
					g_bRot1 = true;
				if (Event.key.keysym.sym == SDLK_DOWN || Event.key.keysym.sym == SDLK_LEFT)
					g_bRot2 = true;
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
