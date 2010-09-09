#ifndef __CLASS_H__
#define __CLASS_H__

#include "./tracked.h"

class CClass : CTracked<TRACKED_CLASS>
{
private:
    int m_iTruc;

public:
    CClass ();
    ~CClass ();
};

#endif //__CLASS_H__
