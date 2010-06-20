//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./main.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MAIN_H__
#define __MAIN_H__

#include "./window_sdl.h"
#include "./hud.h"
#include "../util/index.h"

namespace window {

class CMain : public CWindowSDL
{
private:
    CHUD* m_pHUD;
    bool m_bPauseOn;
    bool m_bPauseOff;
    bool m_bMoveUp;
    bool m_bMoveDown;
    bool m_bMoveLeft;
    bool m_bMoveRight;
    util::CTimerLocal m_Timer;
    float m_fKeyTimeStart;

    void _RenderLoading ();
    void _Event ();

public:
	CMain ();
	virtual ~CMain ();

	virtual void Begin ();
	virtual void End ();
	virtual void Render ();
	virtual void Update ();
    virtual void KeyDown (int c);
    virtual void KeyUp (int c);
    virtual void MouseMotion (int x, int y);
    virtual void MouseButtonUp (const EMouseButton & Button);
};

}; // window

#endif //__MAIN_H__
