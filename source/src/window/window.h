//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./window/window.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_WINDOW_WINDOW_H__
#define __PIRANHA_WINDOW_WINDOW_H__

#include "../util/timer_local.h"
#include <string>

namespace window {

typedef enum
{
	OPTION_ESCAPE_EXIT = 0,
	OPTION_FULLSCREEN = 1,
	OPTION_DOUBLEBUFFER = 2,
	OPTION_UNICODE = 4,
	OPTION_SYNC = 8
}EOption;

typedef enum
{
	CONFIG_NULL = 0,
	CONFIG_FFSA,
	CONFIG_HEIGHT,
	CONFIG_WIDTH,
	CONFIG_COLOR,
	CONFIG_DEPTH,
	CONFIG_STENCIL,
	CONFIG_VIEW_DISTANCE,
	CONFIG_SYNC
}EConfig;

typedef enum
{
	MOUSE_BUTTON_NULL = 0,
	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_RIGHT,
	MOUSE_BUTTON_MIDDLE
}EMouseButton;

#define SYNC_DEFAULT 60.f;
#define WINDOW_HEIGHT       window::CWindow::Height ()
#define WINDOW_WIDTH        window::CWindow::Width ()

class CWindow
{
protected:
	std::string m_szName;
	static unsigned short m_unHeight;
	static unsigned short m_unWidth;
	unsigned char m_ucColor;
	unsigned char m_ucFFSA;
	unsigned char m_ucDepth;
	unsigned char m_ucStencil;
	unsigned int m_uiViewDistance;
	unsigned int m_uiOption;
	bool m_bExit;
	float m_fSync;
    util::CTimerLocal m_TimerSync;

	CWindow ();
	virtual ~CWindow ();

	virtual void Begin () = 0;
	virtual void End () = 0;
	virtual void Render () = 0;
	virtual void Update () = 0;
	virtual void MouseMotion (int x, int y) = 0;
	virtual void MouseButtonDown (const EMouseButton & Button) = 0;
	virtual void MouseButtonUp (const EMouseButton & Button) = 0;
	virtual void KeyDown (int c) = 0;
	virtual void KeyUp (int c) = 0;
    virtual void Swap () = 0;

	void Enable (const EOption & Option);
	void Disable (const EOption & Option);
	void Config (const EConfig & Config, int iValue);

public:
	static unsigned short Height ();// const;
	static unsigned short Width ();// const;
};

}; // window

#endif //__PIRANHA_WINDOW_WINDOW_H__
