//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./util/timer_global.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./timer_global.h"
#include "./state_machine.h"
#include "../window/window_sdl.h"

using namespace util;

CTimerGlobal::CTimerGlobal ()
{
    m_fDecal = 0;
}

CTimerGlobal::~CTimerGlobal ()
{

}

void CTimerGlobal::Init ()
{
	m_fStartTime = SDL_GetTicks () / 1000.f;
    m_fStartDecal = 0.0f;
    m_fDecal = 0.0f;
}

float CTimerGlobal::Time ()
{
    if (!m_fStartDecal)
        m_fTimeCurrent = static_cast<float> (SDL_GetTicks () / 1000.f - m_fStartTime) - m_fDecal;
	return m_fTimeCurrent;
}

void CTimerGlobal::Stop ()
{
    if (!m_fStartDecal)
    {
        CStateMachine::Instance ()->Enable (ENABLED_PAUSE);
        m_fStartDecal = static_cast<float> (SDL_GetTicks () / 1000.f);
    }
}

void CTimerGlobal::Play ()
{
    if (m_fStartDecal)
    {
        CStateMachine::Instance ()->Disable (ENABLED_PAUSE);
        m_fDecal += static_cast<float> (SDL_GetTicks () / 1000.f) - m_fStartDecal;
        m_fStartDecal = 0.f;
    }
}
