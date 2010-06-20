//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./util/tracker.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./tracker.h"
#include "./tracked.h"
#include <string.h>

using namespace util;

CTracker::CTracker ()
{
    memset (m_iCreated, 0, TRACKED_MAX * sizeof (int));
    memset (m_iDeleted, 0, TRACKED_MAX * sizeof (int));
}

CTracker::~CTracker ()
{

}

void CTracker::_Create (const ETracked & Tracked)
{
    m_iCreated[Tracked]++;
}

void CTracker::_Delete (const ETracked & Tracked)
{
    m_iDeleted[Tracked]++;
}

int CTracker::Created (const ETracked & Tracked) const
{
    return m_iCreated[Tracked];
}

int CTracker::Deleted (const ETracked & Tracked) const
{
    return m_iDeleted[Tracked];
}

int CTracker::Leaked (const ETracked & Tracked) const
{
    return m_iCreated[Tracked] - m_iDeleted[Tracked];
}

