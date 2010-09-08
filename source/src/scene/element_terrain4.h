//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./scene/element_terrain4.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_SCENE_ELEMENT_TERRAIN4_H__
#define __PIRANHA_SCENE_ELEMENT_TERRAIN4_H__

#include "./element.h"
#include "../terrain/index.h"

namespace scene {

class CTerrain4 : public CElement
{
    //friend CElement* CManager::_Create (const EType & Type);
	friend class CManager;

private:
    terrain::CTerrain* m_pTerrain;
    float m_fTimeStart;

    CTerrain4 ();
    virtual ~CTerrain4 ();

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

#endif //__PIRANHA_SCENE_ELEMENT_TERRAIN4_H__
