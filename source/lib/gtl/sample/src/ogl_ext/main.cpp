/***********************************************\
	GTL sample : Extensions
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	main.cpp, 03/10/2004
\***********************************************/

#include "./sample.h"

int g_iKeyState = 0;

int main (int argc, char* argv[])
{
/*
    gtl::CMatrix3x3<int> A (2, 3, 1, 3, 4, 1, 1, 1, 1);
    gtl::CMatrix3x3<int> A_inv = A.GetInvert ();
    gtl::CMatrix3x3<int> Identity = A * A_inv;
    printf ("%d, %d, %d\n", A_inv (gtl::X, gtl::X), A_inv (gtl::X, gtl::Y), A_inv (gtl::X, gtl::Z));
    printf ("%d, %d, %d\n", A_inv (gtl::Y, gtl::X), A_inv (gtl::Y, gtl::Y), A_inv (gtl::Y, gtl::Z));
    printf ("%d, %d, %d\n", A_inv (gtl::Z, gtl::X), A_inv (gtl::Z, gtl::Y), A_inv (gtl::Z, gtl::Z));
    printf ("\n");
    printf ("%d, %d, %d\n", Identity (gtl::X, gtl::X), Identity (gtl::X, gtl::Y), Identity (gtl::X, gtl::Z));
    printf ("%d, %d, %d\n", Identity (gtl::Y, gtl::X), Identity (gtl::Y, gtl::Y), Identity (gtl::Y, gtl::Z));
    printf ("%d, %d, %d\n", Identity (gtl::Z, gtl::X), Identity (gtl::Z, gtl::Y), Identity (gtl::Z, gtl::Z));
*/
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
			case SDL_KEYUP:
				if (Event.key.keysym.sym == SDLK_UP)
					g_iKeyState = 0;
				if (Event.key.keysym.sym == SDLK_DOWN)
					g_iKeyState = 0;
				break;
			case SDL_KEYDOWN:
				if (Event.key.keysym.sym == SDLK_ESCAPE)
					bExit = true;
				if (Event.key.keysym.sym == SDLK_UP)
					g_iKeyState = 1;
				if (Event.key.keysym.sym == SDLK_DOWN)
					g_iKeyState = -1;
				break;
			default:
				break;
            }
		}

		if (g_iKeyState == 1)
		{
			g_iAddPosition += 1;
				if (g_iAddPosition > 0)
					g_iAddPosition = 0;	
		}
		else if (g_iKeyState == -1)
			g_iAddPosition -= 1;

		Draw ();

		CWindowSDL::Instance ()->Swap ();
	}

	CWindowSDL::Kill ();
	End ();

	return 0;
}

