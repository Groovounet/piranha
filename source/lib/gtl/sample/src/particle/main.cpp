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
	gtl::CVector3<float> V (0.0f, 2.0f, 2.0f);
	gtl::CVector3<float> N (0.0f, 1.0f, 0.0f);
	gtl::CVector3<float> Proj = V.GetProj (N);
	gtl::CVector3<float> Perp = V.GetPerp (N);

	printf ("V    = (%f, %f, %f)\n", V (gtl::X), V (gtl::Y), V (gtl::Z));
	printf ("N    = (%f, %f, %f)\n", N (gtl::X), N (gtl::Y), N (gtl::Z));
	printf ("Proj = (%f, %f, %f)\n", Proj (gtl::X), Proj (gtl::Y), Proj (gtl::Z));
	printf ("Perp = (%f, %f, %f)\n", Perp (gtl::X), Perp (gtl::Y), Perp (gtl::Z));

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
				if (Event.key.keysym.sym == SDLK_UP)
					g_bRotX1 = false;
				if (Event.key.keysym.sym == SDLK_DOWN)
					g_bRotX2 = false;
				if (Event.key.keysym.sym == SDLK_RIGHT)
					g_bRotZ1 = false;
				if (Event.key.keysym.sym == SDLK_LEFT)
					g_bRotZ2 = false;
				break;
			case SDL_KEYDOWN:
				if (Event.key.keysym.sym == SDLK_ESCAPE)
					bExit = true;
				if (Event.key.keysym.sym == SDLK_UP)
					g_bRotX1 = true;
				if (Event.key.keysym.sym == SDLK_DOWN)
					g_bRotX2 = true;
				if (Event.key.keysym.sym == SDLK_RIGHT)
					g_bRotZ1 = true;
				if (Event.key.keysym.sym == SDLK_LEFT)
					g_bRotZ2 = true;
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
