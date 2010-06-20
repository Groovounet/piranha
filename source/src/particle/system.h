//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-25-2004
//! \file ./particle/system.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_PARTICLE_SYSTEM_H__
#define __PIRANHA_PARTICLE_SYSTEM_H__

#include "../util/index.h"

namespace particle {

#ifdef DEBUG
class CSystem : public util::CTracked<util::TRACKED_PARTICLE>
#else
class CSystem
#endif //DEBUG
{
protected:
    static unsigned int m_uiPointSprite;

public:
    CSystem ();
    virtual ~CSystem ();

    static void Config ();

    virtual bool IsEnd () = 0;
    virtual void Update () = 0;
    virtual void Render () const = 0;
};

}; // particle

#endif //__PIRANHA_PARTICLE_SYSTEM_H__
