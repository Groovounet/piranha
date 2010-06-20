//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-18-2004
//! \file ./util/state_machine.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./state_machine.h"
#include "../particle/index.h"

using namespace util;

CStateMachine::CStateMachine ()
{
    for (int i = CONFIG_NULL; i < STATE_MAX; i++)
        m_Configured[i] = CONFIG_NONE;

    for (int i = CONFIG_NULL; i < STATE_MAX; i++)
        m_Enabled[i] = false;
}

CStateMachine::~CStateMachine ()
{

}

EConfigured CStateMachine::GetConfigured (const EState & State) const
{
    return m_Configured[State];
}

void CStateMachine::SetConfigured (const EState & State, const EConfigured & Configured)
{
    m_Configured[State] = Configured;
}

void CStateMachine::Enable (const EEnabled & Enabled)
{
    m_Enabled[Enabled] = true;
}

void CStateMachine::Disable (const EEnabled & Enabled)
{
    m_Enabled[Enabled] = false;
}

bool CStateMachine::Enabled (const EEnabled & Enabled) const
{
    return m_Enabled[Enabled];
}

void CStateMachine::Init ()
{
    file::CTexture2D::Config ();
    file::CMipmaps2D::Config ();
    file::CRectangle::Config ();
    particle::CDeathPlanet::Config ();
}

void CStateMachine::Log ()
{
    for (int i = CONFIG_NULL; i < STATE_MAX; i ++)
    {
        printf ("State %d : %d\n", i, m_Configured[i]);
    }
}

bool CStateMachine::IsError ()
{
    for (int i = CONFIG_NULL; i < STATE_MAX; i ++)
        if (m_Configured[i] == CONFIG_FAIL)
            return true;
    return false;
}
