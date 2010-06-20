//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-19-2004
//! \file ./util/smart.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_UTIL_SMART_H__
#define __PIRANHA_UTIL_SMART_H__

namespace util {

template <typename T> class CSmart
{
private:
    static T* m_pInstance;

    static int m_iCreated;
    static int m_iDeleted;

protected:
    CSmart ()
    {
        m_iCreated = 0;
        m_iDeleted = 0;
    }

public:
    static T* Create ()
    {
	    if (m_pInstance == 0)
		    m_pInstance = new T;
        m_iCreated++;
        return m_pInstance;
    }

    static void Delete (CSmart* pSmart)
    {
        if (pSmart == m_pInstance)
        {
            m_iDeleted++;
	        if (m_pInstance != 0 && (m_iCreated - m_iDeleted) == 0)
	        {
		        delete m_pInstance;
		        m_pInstance = 0;
	        }
        }
    }

    static int Created ()
    {
        return m_iCreated;
    }

    static int Deleted ()
    {
        return m_iDeleted;
    }

    static int Count ()
    {
        return m_iCreated - m_iDeleted;
    }
};

template <typename T> T* CSmart<T>::m_pInstance = 0;
template <typename T> int CSmart<T>::m_iCreated = 0;
template <typename T> int CSmart<T>::m_iDeleted = 0;

}; // util

#endif //__PIRANHA_UTIL_SMART_H__
