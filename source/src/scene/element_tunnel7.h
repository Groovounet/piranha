//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-26-2004
//! \file ./scene/element_tunnel7.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_SCENE_ELEMENT_TUNNEL7_H__
#define __PIRANHA_SCENE_ELEMENT_TUNNEL7_H__

#include "./element.h"
#include "../file/index.h"
#include "../gl/index.h"

namespace scene {

class CTunnel7 : public CElement
{
    //friend CElement* CManager::_Create (const EType & Type);
	friend class CManager;

    class CStatePlanet : 
        public gl::CStateAuto<GL_DEPTH_TEST>,
        public gl::CStateAuto<GL_LIGHTING>,
        public gl::CStateAuto<GL_TEXTURE_2D>
    {};

private:
    file::CTexture* m_pTextureTunnel;
    file::CTexture* m_pTexturePlanet;
    file::CTexture* m_pTextureClouds;
    gl::CObjectDL* m_pSphere1;
    gl::CObjectDL* m_pSphere2;
    gl::CFade* m_pFade1;
    gl::CFade* m_pFade2;
    float m_fTimeStart;
    gtl::CCamera m_Camera;

    void _RenderPlanet (float fTime) const;
    void _RenderTunnel (float fTime) const;

    CTunnel7 ();
    virtual ~CTunnel7 ();

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

#endif //__PIRANHA_SCENE_ELEMENT_TUNNEL7_H__
