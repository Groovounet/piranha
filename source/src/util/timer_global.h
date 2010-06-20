//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./util/timer_global.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_UTIL_TIMER_GLOBAL_H__
#define __PIRANHA_UTIL_TIMER_GLOBAL_H__

#include "./singleton.h"

namespace util {

class CTimerGlobal : public CSingleton<CTimerGlobal>
{
    friend class CSingleton<CTimerGlobal>;

private:
    float m_fStartTime;
    float m_fDecal;
    float m_fStartDecal;
    float m_fTimeCurrent;

	CTimerGlobal ();
    ~CTimerGlobal ();
    
public:
	void Stop ();
    void Play ();
	void Init ();
	float Time ();
};

}; // util

#endif //__PIRANHA_UTIL_TIMER_GLOBAL_H__
