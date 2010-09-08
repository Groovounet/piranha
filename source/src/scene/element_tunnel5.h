//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-29-2004
//! \file ./scene/element_tunnel5.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_SCENE_ELEMENT_TUNNEL5_H__
#define __PIRANHA_SCENE_ELEMENT_TUNNEL5_H__

#include "./element.h"
#include "../file/index.h"
#include "../gl/index.h"

namespace scene {

class CTunnel5 : public CElement
{
    //friend CElement* CManager::_Create (const EType & Type);
	friend class CManager;

private:
    file::CTexture* m_pTextureTunnel;
    file::CTexture* m_pTexturePlanet;
    file::CTexture* m_pTextureClouds;
    //unsigned int m_uiTextureMotionBlur;

    void _RenderTunnel (float fTime) const;

    CTunnel5 ();
    virtual ~CTunnel5 ();

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

#endif //__PIRANHA_SCENE_ELEMENT_TUNNEL5_H__
