//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 18-12-2004
//! \file ./scene/element_explode2.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_SCENE_ELEMENT_EXPLODE2_H__
#define __PIRANHA_SCENE_ELEMENT_EXPLODE2_H__

#include "./element.h"
#include "../file/index.h"
#include "../gl/index.h"
#include <list>

namespace scene {

class CExplode2 : public CElement
{
    friend CElement* CManager::_Create (const EType & Type);

    typedef struct
    {
        float m_fTimeStart;
        float m_fRotate[3];
    } SRay;

private:
    file::CTexture* m_pTextureColormap1;
    file::CTexture* m_pTextureColormap2;
    file::CTexture* m_pTextureNormalmap;
    file::CTexture* m_pTextureLightmap;
    file::CTexture* m_pTextureClouds1;
    file::CTexture* m_pTextureClouds2;
    file::CTexture* m_pTextureFade1;
    gl::CObjectDL* m_pSphere1;
    gl::CObjectDL* m_pSphere2;
    gl::CObjectDL* m_pDisk1;
    gl::CFade* m_pFade1;
    float m_fTimeStart;
    float m_fTimeExplode;
    float m_fTimeRay;
    std::list<SRay> m_Ray;
    unsigned int m_uiRay;

    CExplode2 ();
    virtual ~CExplode2 ();

    void _RenderCylinder (float fRadius, float fLenght, float fDivision) const;
    void _RenderPlanet (bool bDark) const;
    void _RenderRay (float fTime) const;
    void _Render1 (float fTime) const;
    void _Render2 (float fTime) const;

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

#endif //__PIRANHA_SCENE_ELEMENT_EXPLODE2_H__
