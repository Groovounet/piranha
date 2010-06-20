//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-13-2004
//! \file ./piranha/particle/fountain.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_PARTICLE_FOUNTAIN_H__
#define __PIRANHA_PARTICLE_FOUNTAIN_H__

#include "./system.h"
#include "./manager.h"

namespace particle {

class CFountain
{
    friend CFountain* CManager::CreateFountain ();

private:
    CFountain ();
    virtual ~CFountain ();

public:

};

}; // particle

#endif //__PIRANHA_PARTICLE_FOUNTAIN_H__
