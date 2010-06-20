//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-24-2004
//! \file ./piranha/particle/manager.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./manager.h"
#include "./system_cube.h"
#include "./system_trail.h"
#include "./system_explode.h"
#include "./system_death_planet.h"
#include "./system_fire.h"
#include "./system_fountain.h"
#include "./system_smoke.h"
#include "./system_stars.h"

using namespace particle;

CManager::CManager ()
{
	for (int i = 0; i < SYSTEM_MAX; i++)
		m_pSystem[i] = 0;
}

CManager::~CManager ()
{
	for (int i = 0; i < SYSTEM_MAX; i++)
		if (m_pSystem[i])
			_Kill (i);
}

void CManager::Update ()
{
	for (int i = 0; i < SYSTEM_MAX; i++)
	{
		if (m_pSystem[i])
		{
			m_pSystem[i]->Update ();
			if (m_pSystem[i]->IsEnd ())
			{
				_Kill (i);
				continue;
			}
		}
	}
}

void CManager::Render () const
{
	for (int i = 0; i < SYSTEM_MAX; i++)
		if (m_pSystem[i])
            m_pSystem[i]->Render ();
}

void CManager::Clean ()
{
    for (int i = 0; i < SYSTEM_MAX; i++)
    {
        if (m_pSystem[i])
            _Kill (i);
    }
}

CCube* CManager::CreateCube ()
{
	int iIndex = _FindFreeIndex ();
	return static_cast<CCube*> (iIndex != -1 ? m_pSystem[iIndex] = new CCube : 0);
}

CDeathPlanet* CManager::CreateDeathPlanet ()
{
	int iIndex = _FindFreeIndex ();
	return static_cast<CDeathPlanet*> (iIndex != -1 ? m_pSystem[iIndex] = new CDeathPlanet : 0);
}

CExplode* CManager::CreateExplode ()
{
	int iIndex = _FindFreeIndex ();
	return static_cast<CExplode*> (iIndex != -1 ? m_pSystem[iIndex] = new CExplode : 0);
}

CStars* CManager::CreateStars ()
{
	int iIndex = _FindFreeIndex ();
	return static_cast<CStars*> (iIndex != -1 ? m_pSystem[iIndex] = new CStars : 0);
}

CTrail* CManager::CreateTrail ()
{
	int iIndex = _FindFreeIndex ();
	return static_cast<CTrail*> (iIndex != -1 ? m_pSystem[iIndex] = new CTrail : 0);
}

void CManager::_Kill (unsigned int uiIndex)
{
	delete m_pSystem[uiIndex];
	m_pSystem[uiIndex] = 0;
}

int CManager::_FindFreeIndex () const
{
	for (int i = 0; i < SYSTEM_MAX; i++)
		if (m_pSystem[i] == 0)
			return i;
	return -1;
}
