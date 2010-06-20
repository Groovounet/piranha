//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 03/10/2004
//! \file fps.h
//! \brief Déclaration du compteur de FPS.
//////////////////////////////////////////////////////////////////////////////

#ifndef FPS_H
#define FPS_H

#include "./timer.h"

#define TIME_TO_COUNT 1.f

class CFPSCounter 
{
private:
	CTimerSDL m_Timer;
	short m_nFpsBuffer;
	short m_nFps;
	float m_fTimeToCount;

public:
	CFPSCounter ();
	
	void Init ();
	short GetFPS () const;
	void Update ();
	float GetTimeToCount ();
	void SetTimeToCount (float fTimeToCount);
};

#endif //FPS_H
