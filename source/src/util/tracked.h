//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./util/tracked.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __TRACKED_H__
#define __TRACKED_H__

#include "./tracker.h"

namespace util {

template <ETracked T> class CTracked
{
protected:
    CTracked ()
    {
        CTracker::Instance ()->_Create (T);
    }

    ~CTracked ()
    {
        CTracker::Instance ()->_Delete (T);
    }
};

}; // util

#endif //__TRACKED_H__


