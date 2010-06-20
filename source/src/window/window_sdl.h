//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-10-2004
//! \file ./window/window_sdl.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_WINDOW_WINDOW_SDL_H__
#define __PIRANHA_WINDOW_WINDOW_SDL_H__

#include "./window.h"
#include "../util/common.h"

namespace window {

class CWindowSDL : public CWindow
{
	static CWindowSDL* m_pWindow;

private:
	SDL_Surface* m_pSurface;
	bool m_bEscapeExit;
	bool m_bFirst;

	void _Resize ();
	void _Create ();

protected:
	CWindowSDL ();
	virtual ~CWindowSDL ();

	virtual void Begin () {}
	virtual void End () {}
	virtual void Render () {}
	virtual void Update () {}
	virtual void MouseMotion (int x, int y) {}
	virtual void MouseButtonDown (const EMouseButton & Button) {}
	virtual void MouseButtonUp (const EMouseButton & Button) {}
	virtual void KeyDown (int c) {}
	virtual void KeyUp (int c) {}
    virtual void Swap ();

    void SetName (const char* szFilename);
    const char* GetName () const;

public:
	void Run ();
	void Exit ();
};

}; // window

#endif //__PIRANHA_WINDOW_WINDOW_SDL_H__
