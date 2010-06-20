//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./util/tracker.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __TRACKER_H__
#define __TRACKER_H__

#include "./singleton.h"

namespace util {

// 12-17-2004 - NOTE : To track an object, add a value in "ETracked".
typedef enum
{
    TRACKED_NULL = 0,
    TRACKED_SHADER,
    TRACKED_OBJECT,
    TRACKED_TEXTURE,
    TRACKED_PARTICLE,
    TRACKED_SCENE,
    TRACKED_STATE,
    TRACKED_FADE,
    TRACKED_MAX
} ETracked;

class CTracker : public CSingleton<CTracker>
{
    friend class CSingleton<CTracker>;

private:
    int m_iCreated[TRACKED_MAX];
    int m_iDeleted[TRACKED_MAX];

    CTracker ();
    ~CTracker ();

// 17-12/2004 - BUG : Must be private
public:
    void _Create (const ETracked & Tracked);
    void _Delete (const ETracked & Tracked);

public:
    int Created (const ETracked & Tracked) const;
    int Deleted (const ETracked & Tracked) const;
    int Leaked (const ETracked & Tracked) const;
};

}; // util

#endif //__TRACKER_H__
