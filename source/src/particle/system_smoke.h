//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-13-2004
//! \file ./particle/smoke.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_PARTICLE_SMOKE_H__
#define __PIRANHA_PARTICLE_SMOKE_H__

#include "./system.h"
#include "./manager.h"

namespace particle {

class CSmoke
{
    friend CSmoke* CManager::CreateSmoke ();

private:
    CSmoke ();
    virtual ~CSmoke ();

public:

};

}; // particle

#endif //__PIRANHA_PARTICLE_SMOKE_H__
