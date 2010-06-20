#include "./tracker.h"
#include "./tracked.h"
#include <string.h>

CTracker* CTracker::m_pInstance = 0;

CTracker::CTracker ()
{
    memset (m_iCreated, 0, TRACKED_MAX * sizeof (int));
    memset (m_iDeleted, 0, TRACKED_MAX * sizeof (int));
}

CTracker::~CTracker ()
{

}

CTracker* CTracker::Instance ()
{
	if (m_pInstance == 0)
		m_pInstance = new CTracker;
	return m_pInstance;
}

void CTracker::Kill ()
{
	if (m_pInstance != 0)
	{
		delete m_pInstance;
		m_pInstance = 0;
	}
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

