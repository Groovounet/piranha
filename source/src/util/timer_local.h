//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./util/timer_local.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_UTIL_TIMER_LOCAL_H__
#define __PIRANHA_UTIL_TIMER_LOCAL_H__

namespace util {

class CTimerLocal
{
private:
	float m_fStartTime;

public:
	CTimerLocal ();
	
	void Init ();
	float Time () const;
};

}; // util

#endif //__PIRANHA_UTIL_TIMER_LOCAL_H__
