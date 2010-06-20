//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-10-2004
//! \file ./piranha/particle/fire.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_PARTICLE_FIRE_H__
#define __PIRANHA_PARTICLE_FIRE_H__

#include "./system.h"
#include "./manager.h"

namespace particle {

class CFire
{
    friend CFire* CManager::CreateFire ();

private:
    CFire ();
    virtual ~CFire ();

public:

};

}; // particle

#endif //__PIRANHA_PARTICLE_FIRE_H__
