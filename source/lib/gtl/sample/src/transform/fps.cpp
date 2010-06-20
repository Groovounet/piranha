//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 03/10/2004
//! \file fps.cpp
//! \brief Définition du compteur de FPS.
//////////////////////////////////////////////////////////////////////////////

#include "./fps.h"

CFPSCounter::CFPSCounter ()
{
	m_fTimeToCount = TIME_TO_COUNT;
	Init ();
}

float CFPSCounter::GetTimeToCount ()
{
	return m_fTimeToCount;
}

void CFPSCounter::SetTimeToCount (float fTimeToCount)
{
	m_fTimeToCount = fTimeToCount;
}

void CFPSCounter::Init ()
{
	m_Timer.Init ();
	m_nFpsBuffer = 0;
	m_nFps = 0;	
}

short CFPSCounter::GetFPS () const
{
	return m_nFps;
}

void CFPSCounter::Update ()
{
	m_nFpsBuffer++;
	
	if (m_Timer.GetTime () >= m_fTimeToCount)
	{
		m_nFps = m_nFpsBuffer;
		m_nFpsBuffer = 0;
		m_Timer.Init ();
	}
}
