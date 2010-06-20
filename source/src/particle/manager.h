//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-24-2004
//! \file ./piranha/particle/manager.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_PARTICLE_MANAGER_H__
#define __PIRANHA_PARTICLE_MANAGER_H__

#include "./system.h"
#include "../util/singleton.h"

namespace particle {

#define SYSTEM_MAX 1024

class CCube;
class CDeathPlanet;
class CExplode;
class CFire;
class CFountain;
class CSmoke;
class CStars;
class CTrail;

class CManager : public util::CSingleton<CManager>
{
    friend class util::CSingleton<CManager>;

private:
    CSystem*            m_pSystem[SYSTEM_MAX];

	                    CManager ();
	                    ~CManager ();

	int                 _FindFreeIndex () const;
	void                _Kill (unsigned int uiIndex);

public:
	CCube*              CreateCube ();
    CDeathPlanet*       CreateDeathPlanet ();
    CExplode*           CreateExplode ();
    CFire*              CreateFire ();
    CFountain*          CreateFountain ();
    CSmoke*             CreateSmoke ();
    CStars*             CreateStars ();
    CTrail*             CreateTrail ();

    void                Render () const;
	void                Update ();
    void                Clean ();
};

}; // particle

#endif //__PIRANHA_PARTICLE_MANAGER_H__
