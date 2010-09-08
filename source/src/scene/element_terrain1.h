//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./scene/element_terrain1.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_SCENE_ELEMENT_TERRAIN1_H__
#define __PIRANHA_SCENE_ELEMENT_TERRAIN1_H__

#include "./element.h"
#include "../terrain/index.h"

namespace scene {

class CTerrain1 : public CElement
{
    //friend CElement* CManager::_Create (const EType & Type);
	friend class CManager;

private:
    terrain::CTerrain* m_pTerrain;
    file::CTexture2D* m_pTunnelTex;
    float m_fTimeStart;
    unsigned int m_uiTextureMotionBlur;
    int m_iTextureType;

    CTerrain1 ();
    virtual ~CTerrain1 ();

    void _RenderTunnel (float fTime) const;

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

#endif //__PIRANHA_SCENE_ELEMENT_TERRAIN_H__
