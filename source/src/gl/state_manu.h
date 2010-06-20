//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./util/state_manu.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_UTIL_STATE_MANU_H__
#define __PIRANHA_UTIL_STATE_MANU_H__

#include "../util/common.h"
#include "../util/tracked.h"

namespace gl {

#ifdef DEBUG
template<unsigned int N> class CStateManu : public util::CTracked<util::TRACKED_STATE>
#else
template<unsigned int N> class CStateManu
#endif //DEBUG
{
private:
    struct SState
    {
        GLenum m_Flag;
        GLboolean m_bState;
    };

    SState m_State[N];

public:
    void Enable ()
    {
        for (unsigned int i = 0; i < N; i++)
        {
            m_State[i].m_bState = glIsEnabled (m_State[i].m_Flag);
            if (!m_State[i].m_bState)
                glEnable (m_State[i].m_Flag);
        }
    }

    void Disable ()
    {
        for (unsigned int i = 0; i < N; i++)
        {
            if (!m_State[i].m_bState)
                glDisable (m_State[i].m_Flag);
        }
    }

	GLenum& operator[] (unsigned int i)
	{
        if (i >= N)
            return m_State[0].m_Flag;
		return m_State[i].m_Flag;
	}

    void Init (unsigned int i, GLenum Flag)
    {
        if (i >= N)
            return;
        m_State[i].m_Flag = Flag;
    }
};

}; // gl

#endif //__PIRANHA_UTIL_STATE_MANU_H__
