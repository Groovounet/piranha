//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-04-2004
//! \file ./piranha/scene/element_title.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_SCENE_ELEMENT_TITLE_H__
#define __PIRANHA_SCENE_ELEMENT_TITLE_H__

#include "./element.h"
#include "../file/index.h"
#include "../gl/index.h"

namespace scene {

class CTitle : public CElement
{
	friend class CManager;

private:
    file::CTexture*                 m_pTexture1;
    file::CTexture*                 m_pTexture2;
    gl::CObjectDL*                  m_pObject;
    gl::CShader*                    m_pShader;
    int                             m_iVarTexture1;
    int                             m_iVarTexture2;
    int                             m_iVarTime;
    float                           m_fTimeStart;

    CTitle ();
    virtual ~CTitle ();

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

#endif //__PIRANHA_SCENE_ELEMENT_TITLE_H__
