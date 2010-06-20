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
			case SDL_KEYDOWN:
				bExit = true;
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

