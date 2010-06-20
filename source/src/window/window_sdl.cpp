//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./window/window_sdl.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./window_sdl.h"
#include "./hud.h"
#include "../util/timer_global.h"

using namespace window;

CWindowSDL::CWindowSDL ()
{
	m_bEscapeExit = false;//true;
    m_pSurface = 0;
}

CWindowSDL::~CWindowSDL ()
{
    window::CHUD::Kill ();
    //! 01/01/2005 - BUGS : Under Linux and in fullscreen mode, the mouse cursor don't move have the end of Piranha if cursor drawing isn't enabled.
    SDL_ShowCursor (SDL_ENABLE);
    if (m_pSurface)
        SDL_FreeSurface (m_pSurface);
}

void CWindowSDL::Run ()
{
	_Create ();
	Begin ();

    while (!m_bExit)
    {
		if (m_uiOption & OPTION_UNICODE)
			SDL_EnableUNICODE (1);
		else
			SDL_EnableUNICODE (0);

		SDL_Event Events;

		while (SDL_PollEvent (&Events))
		{
			if (Events.type == SDL_QUIT)
			{
				m_bExit = true;
			}
			else if (Events.type == SDL_KEYDOWN)
			{
				if (m_bEscapeExit)
					m_bExit = true;
				KeyDown (Events.key.keysym.sym);
			}
			else if (Events.type == SDL_KEYUP)
			{
				KeyUp (Events.key.keysym.sym);
			}
			else if (Events.type == SDL_MOUSEMOTION)
			{
				SDL_MouseMotionEvent *pEvent = (SDL_MouseMotionEvent*) &Events;
				MouseMotion (pEvent->x, pEvent->y);
			}
			else if (Events.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_MouseButtonEvent *pEvent = (SDL_MouseButtonEvent*) &Events;
				EMouseButton Button;

				switch (pEvent->button)
				{
				default:
					Button = MOUSE_BUTTON_NULL;
					break;
				case SDL_BUTTON_LEFT:
					Button = MOUSE_BUTTON_LEFT;
					break;
				case SDL_BUTTON_RIGHT:
					Button = MOUSE_BUTTON_RIGHT;
					break;
				case SDL_BUTTON_MIDDLE:
					Button = MOUSE_BUTTON_MIDDLE;
					break;
				}

				if (Button != MOUSE_BUTTON_NULL)
					MouseButtonDown (Button);
			}
			else if (Events.type == SDL_MOUSEBUTTONUP)
			{
				SDL_MouseButtonEvent *pEvent = (SDL_MouseButtonEvent*) &Events;
				EMouseButton Button;

				switch (pEvent->button)
				{
				default:
					Button = MOUSE_BUTTON_NULL;
					break;
				case SDL_BUTTON_LEFT:
					Button = MOUSE_BUTTON_LEFT;
					break;
				case SDL_BUTTON_RIGHT:
					Button = MOUSE_BUTTON_RIGHT;
					break;
				case SDL_BUTTON_MIDDLE:
					Button = MOUSE_BUTTON_MIDDLE;
					break;
				}

				if (Button != MOUSE_BUTTON_NULL)
					MouseButtonUp (Button);
			}
		}

		if (!(m_uiOption & CONFIG_SYNC))
		{
			Update ();
			Render ();
			Swap ();
		}
        // 14/11/2004 - TODO : Use a local timer to vertical sync
        else if (m_TimerSync.Time () >= m_fSync)
		{
            m_TimerSync.Init ();
            Update ();
			Render ();			
			Swap ();
        }
	}

	End ();
}

void CWindowSDL::Exit ()
{
	m_bExit = true;
}

void CWindowSDL::Swap ()
{
#ifdef DEBUG
    int iCodeErreur;
	if ((iCodeErreur = glGetError ()) != GL_NO_ERROR)
	{
		const char* szMsgError = (const char*) gluErrorString (iCodeErreur);
		//fprintf (stderr, "Erreur OpenGL : %s\n", szMsgError);
        printf ("Erreur OpenGL : %s\n", szMsgError);
	}
#endif //DEBUG

    SDL_GL_SwapBuffers ();
}

const char* CWindowSDL::GetName () const
{
    return m_szName.c_str ();
}

void CWindowSDL::SetName (const char* szFilename)
{
    m_szName = std::string (szFilename);
    SDL_WM_SetCaption (m_szName.c_str (), m_szName.c_str ());
}

void CWindowSDL::_Create ()
{
    if (SDL_Init (SDL_INIT_VIDEO) < 0)
		return;

	int iVideoConf = SDL_OPENGL | SDL_HWPALETTE | SDL_HWSURFACE | SDL_HWACCEL;
	if (m_uiOption & OPTION_FULLSCREEN)
		iVideoConf |= SDL_FULLSCREEN;

	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, m_uiOption & OPTION_DOUBLEBUFFER ? 1 : 0);
    SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, m_ucDepth);
    SDL_GL_SetAttribute (SDL_GL_STENCIL_SIZE, m_ucStencil);

	if ((m_pSurface = SDL_SetVideoMode (m_unWidth, m_unHeight, m_ucColor, iVideoConf)) == 0)
		return;

    SDL_WM_SetCaption (m_szName.c_str (), m_szName.c_str ());
    SDL_ShowCursor (SDL_DISABLE);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	_Resize ();
}

void CWindowSDL::_Resize ()
{
	if (m_unHeight == 0)
		m_unHeight = 1;

    glViewport (0, 0, m_unWidth, m_unHeight);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    gluPerspective (
		45.f,
		static_cast<float>(m_unWidth) / static_cast<float>(m_unHeight),
		0.1f,
		static_cast<float>(m_uiViewDistance));

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}
