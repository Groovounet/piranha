//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./piranha/scene/manager.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_SCENE_MANAGER_H__
#define __PIRANHA_SCENE_MANAGER_H__

#include "../util/index.h"

namespace scene {

#define SCENE_MAX       32

typedef enum
{
	TYPE_NULL = 0,
	TYPE_LOADING,
    TYPE_AUTHOR,
	TYPE_TITLE,
    TYPE_FADE,
    TYPE_TUNNEL1,
    TYPE_TUNNEL2,
    TYPE_TUNNEL3,
    TYPE_TUNNEL4,
    TYPE_TUNNEL5,
    TYPE_TUNNEL6,
    TYPE_TUNNEL7,
    TYPE_TUNNEL8,
    TYPE_TERRAIN1,
    TYPE_TERRAIN2,
    TYPE_TERRAIN3,
    TYPE_TERRAIN4,
    TYPE_TERRAIN5,
    TYPE_TERRAIN6,
    TYPE_TERRAIN7,
    TYPE_EXPLODE1,
    TYPE_EXPLODE2,
    TYPE_EXPLODE3,
    TYPE_CREDITS
}EType;

class CElement;

class CManager : public util::CSingleton<CManager>
{
    friend class util::CSingleton<CManager>;

private:
    unsigned int        m_iSceneIndex;
    unsigned int        m_iSceneSize;
    bool                m_bFirst;

    CElement*           m_pScene[SCENE_MAX];

	                    CManager ();
	                    ~CManager ();

	int                 _FindFreeIndex () const;
	void                _Kill (unsigned int uiIndex);
	CElement*           _Create (const EType & Type);

public:
    bool                Load ();
    void                Begin ();
    void                End ();
    void                Update ();
    void                Render () const;
    bool                Push (const EType & Type);
};

}; // scene

#endif //__PIRANHA_SCENE_MANAGER_H__
