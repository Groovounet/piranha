//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 01-09-2005
//! \file ./util/factory.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_UTIL_FACTORY_H__
#define __PIRANHA_UTIL_FACTORY_H__

namespace util {

template <typename T> class CFactory
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

template <typename Key, class Object> class Factory
{
public:
    typedef Object *(*Create) ();
    typedef void (*Delete) (Object *);

    typedef struct
    {
        Create m_Create;
        Delete m_Delete;
    } SFunc;

    map<Key, SFunc> m_Registred;

    bool Register (const Key & key, Creator creator)
    {
        if (m_Objects.find (key) != m_Registred.end ())
            return false;
        m_Registred.insert (pair<Key, Creator> (key, creator));
        return true;
    }

    Object* Create (Key key)
    {
        Object *object;

        map<Key, Creator>::iterator it = m_Registred.find (key);
        if (it == m_Registred.end())
            return 0;

        Creator creator = (*it).second;
        return (*creator)();
    }
};

}; // util

#endif //__PIRANHA_UTIL_FACTORY_H__

