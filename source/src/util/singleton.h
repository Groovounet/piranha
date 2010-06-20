//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./util/singleton.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_UTIL_SINGLETON_H__
#define __PIRANHA_UTIL_SINGLETON_H__

namespace util {

// 12-17-2004 NOTE : The CSingleton derived class must to allow CSingleton to create it instance.
// A solution is to declare public the contrutor and the destructor functions.
// An other, witch is better, is to declare friend CSingleton in the derived class.
template <typename T> class CSingleton
{
private:
    static T* m_pInstance;

public:
    static T* Instance ()
    {
	    if (m_pInstance == 0)
		    m_pInstance = new T;
	    return m_pInstance;
    }

    static void Kill ()
    {
	    if (m_pInstance != 0)
	    {
		    delete m_pInstance;
		    m_pInstance = 0;
	    }
    }
};

template <typename T> T* CSingleton<T>::m_pInstance = 0;

}; // util

#endif //__PIRANHA_UTIL_SINGLETON_H__
