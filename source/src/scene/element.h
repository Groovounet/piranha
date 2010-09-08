//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./scene/element.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SCENE_ELEMENT_H__
#define __SCENE_ELEMENT_H__

#include "./manager.h"
#include "../util/index.h"

namespace scene {

#ifdef DEBUG
class CElement : public util::CTracked<util::TRACKED_SCENE>
#else
class CElement
#endif //DEBUG
{
    //friend void CManager::_Kill (unsigned int uiIndex);
	friend class CManager;

protected:
    CElement ();
    virtual ~CElement ();

    float m_fTimeStart;

public:
    virtual bool Load () = 0;
    virtual void Begin () = 0;
	virtual void End () = 0;
    virtual bool IsEnd () = 0;
    virtual void Update () = 0;
    virtual void Render () const = 0;
    virtual EType Type () = 0;
    virtual bool HUD () = 0;
};

}; // scene

#endif //__SCENE_ELEMENT_H__
