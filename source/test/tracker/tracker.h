#ifndef __TRACKER_H__
#define __TRACKER_H__

typedef enum
{
    TRACKED_NULL = 0,
    TRACKED_CLASS,
    TRACKED_MAX
} ETracked;

class CTracker
{
private:
    static CTracker* m_pInstance;
    int m_iCreated[TRACKED_MAX];
    int m_iDeleted[TRACKED_MAX];

    CTracker ();
    ~CTracker ();

// 17-12/2004 - BUG : Must be private
public:
    void _Create (const ETracked & Tracked);
    void _Delete (const ETracked & Tracked);

public:
    static CTracker* Instance ();
    static void Kill ();

    int Created (const ETracked & Tracked) const;
    int Deleted (const ETracked & Tracked) const;
    int Leaked (const ETracked & Tracked) const;
};

#endif //__TRACKER_H__
