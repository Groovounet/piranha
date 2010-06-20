/***********************************************\
	GTL sample
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	window_sdl.h, 02/10/2004
\***********************************************/

#ifndef WINDOW_SDL_H
#define WINDOW_SDL_H

#include "../../../include/gtl.h"
#ifdef WIN32
#include "../../lib/sdl/include/SDL.h"
#else
#include <SDL.h>
#endif 

class CWindowSDL
{
	static CWindowSDL* m_pInstance;

private:
	unsigned short m_unHeight;
	unsigned short m_unWidth;
	unsigned char m_ucColor;
	bool m_bFullscreen;
	bool m_bCreate;
	SDL_Surface* m_pSurface;

	void _Resize (unsigned short unWidth, unsigned short unHeight);

	CWindowSDL ();
	~CWindowSDL ();

public:
	static CWindowSDL* Instance ();
	static void Kill ();
	static bool IsCreate ();

	void Swap ();
	bool Create (const char* szName, unsigned short unWidth, unsigned short unHeight, unsigned char ucColor, bool bFullscreen);

	unsigned short GetHeight () const;
	unsigned short GetWidth () const;
	unsigned char GetColor () const;
	bool GetFullscreen () const;
};

#endif //WINDOW_SDL_H

