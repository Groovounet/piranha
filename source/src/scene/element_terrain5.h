//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./scene/element_terrain5.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_SCENE_ELEMENT_TERRAIN5_H__
#define __PIRANHA_SCENE_ELEMENT_TERRAIN5_H__

#include "./element.h"
#include "../terrain/index.h"

namespace scene {

class CTerrain5 : public CElement
{
    friend CElement* CManager::_Create (const EType & Type);

private:
    terrain::CTerrain* m_pTerrain;
    float m_fTimeStart;
    unsigned int m_uiTextureMotionBlur;
    int m_iTextureType;
    float m_fTimeQuake;
    gtl::CVector2<float> m_Quake;

    CTerrain5 ();
    virtual ~CTerrain5 ();

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

#endif //__PIRANHA_SCENE_ELEMENT_TERRAIN5_H__
