//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-21-2004
//! \file ./piranha/scene/element_explode1.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_SCENE_ELEMENT_EXPLODE1_H__
#define __PIRANHA_SCENE_ELEMENT_EXPLODE1_H__

#include "./element.h"
#include "../file/index.h"
#include "../gl/index.h"
#include <list>

namespace scene {

class CExplode1 : public CElement
{
	friend class CManager;

private:
    file::CTexture* m_pTextureColormap;
    file::CTexture* m_pTextureNormalmap;
    file::CTexture* m_pTextureLightmap;
    file::CTexture* m_pTextureClouds;
    gl::CObjectDL* m_pSphere1;
    gl::CObjectDL* m_pSphere2;
    gl::CFade* m_pFade1;
    float m_fTimeStart;
    float m_fTimeExplode;

    CExplode1 ();
    virtual ~CExplode1 ();

    void _RenderPlanet () const;

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

#endif //__PIRANHA_SCENE_ELEMENT_EXPLODE1_H__
