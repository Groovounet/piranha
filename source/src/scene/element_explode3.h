//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-23-2004
//! \file ./scene/element_explode3.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_SCENE_ELEMENT_EXPLODE3_H__
#define __PIRANHA_SCENE_ELEMENT_EXPLODE3_H__

#include "./element.h"
#include "../gl/index.h"
#include "../file/index.h"
#include <list>

namespace scene {

class CExplode3 : public CElement
{
    //friend CElement* CManager::_Create (const EType & Type);
	friend class CManager;

private:
    float m_fTimeStart;
    float m_fTimeExplode;
    gl::CFade* m_pFade1;
    file::CTexture* m_pTextureFade1;

    CExplode3 ();
    virtual ~CExplode3 ();

public:
    virtual bool Load ();
    virtual void Begin ();
	virtual void End ();
    virtual bool IsEnd ();
    virtual void Update ();
    virtual void Render () const;
    virtual EType Type ();
    virtual bool HUD ();
};

}; // scene

#endif //__PIRANHA_SCENE_ELEMENT_EXPLODE3_H__
