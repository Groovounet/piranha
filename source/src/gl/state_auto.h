//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-29-2004
//! \file ./util/state_auto.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_UTIL_STATE_AUTO_H__
#define __PIRANHA_UTIL_STATE_AUTO_H__

#include "../util/common.h"
#include "../util/tracked.h"

namespace gl {

#ifdef DEBUG
template<GLenum Flag> class CStateAuto : public util::CTracked<util::TRACKED_STATE>
#else
template<GLenum Flag> class CStateAuto
#endif //DEBUG
{
private:
    GLboolean m_bState;

public:
    CStateAuto ()
    {
        m_bState = glIsEnabled (Flag);
        if (!m_bState)
            glEnable(Flag);
    }

    ~CStateAuto()
    {
        if (!m_bState)
            glDisable (Flag);
    }
};

}; // gl

#endif //__PIRANHA_UTIL_STATE_AUTO_H__
