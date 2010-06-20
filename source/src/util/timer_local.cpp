//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./util/timer_local.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./timer_local.h"
#include "./common.h"

using namespace util;

CTimerLocal::CTimerLocal ()
{

}

void CTimerLocal::Init ()
{
	m_fStartTime = SDL_GetTicks () / 1000.f;
}

float CTimerLocal::Time () const
{
	return (static_cast<float> (SDL_GetTicks () / 1000.f - m_fStartTime));
}
