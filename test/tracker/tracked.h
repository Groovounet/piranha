#ifndef __TRACKED_H__
#define __TRACKED_H__

#include "./tracker.h"

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

#endif //__TRACKED_H__


