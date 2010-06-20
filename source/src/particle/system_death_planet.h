//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-23-2004
//! \file ./particle/system_death_planet.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_PARTICLE_DEATH_PLANET_H__
#define __PIRANHA_PARTICLE_DEATH_PLANET_H__

#include "./system.h"
#include "./manager.h"
#include "../util/index.h"
#include "../file/texture.h"

namespace particle {

class CDeathPlanet : public CSystem
{
    friend CDeathPlanet* CManager::CreateDeathPlanet ();

    typedef struct SParticle
    {
	    float m_fTimeLife;
        gtl::CVector3<float> m_Position;
        gtl::CColor4<float> m_Color;
    } TParticle;

private:
    float m_fParticleSize;
    gtl::CVector3<float> m_Position;
	float m_fRadius;
    unsigned int m_uiParticle;
    float m_fTimeLife;
    gtl::CColor4<float> m_Color;
    float m_fTimeStart;

    TParticle* m_pParticle;
    file::CTexture* m_pTexture;

    CDeathPlanet ();
    virtual ~CDeathPlanet ();

    void _Init ();

public:
	static const CDeathPlanet* Create (
        float fParticleSize, 
        const gtl::CVector3<float> & Position, 
        float fRadius,
        unsigned int uiParticle,
        float fTimeLife, 
        const gtl::CColor4<float> & Color);

    virtual bool IsEnd ();
	virtual void Update ();
    virtual void Render () const;
//    virtual void End ();
//    virtual bool Load ();
};

}; // particle

#endif //__PIRANHA_PARTICLE_DEATH_PLANET_H__
