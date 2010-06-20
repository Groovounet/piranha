//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-26-2004
//! \file ./particle/trail.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_PARTICLE_TRAIL_H__
#define __PIRANHA_PARTICLE_TRAIL_H__

#include "./system.h"
#include "./manager.h"
#include "../file/index.h"
#include "../util/index.h"

namespace particle {

class CTrail : public CSystem
{
    friend CTrail* CManager::CreateTrail ();

    typedef struct SParticle
    {
        SParticle* m_pNext;
        gtl::CVector3<float> m_Position;
        gtl::CColor4<float> m_Color;
        float m_fTimeStart;
    } TParticle;

private:
    gtl::CVector3<float> m_Position;
    gtl::CVector3<float> m_Speed;
    gtl::CVector3<float> m_Acceleration;
    gtl::CColor4<float> m_Color;
    float m_fParticleSize;
    float m_fTimeStart;
    float m_fTimeSystem;
    float m_fTimeParticle;
    float m_fTimeInterval;
    float m_fTimeCreated;
    TParticle* m_pParticleFirst;
    TParticle* m_pParticleLast;
    file::CTexture* m_pTexture;

    CTrail ();
    virtual ~CTrail ();

    void _Init ();

public:
	static const CTrail* Create (
        const gtl::CVector3<float> & Position,
        const gtl::CVector3<float> & Speed,
        const gtl::CVector3<float> & Acceleration,
        const gtl::CColor4<float> & Color,
        float fParticleSize, 
        float fTimeSystem,
        float fTimeParticle);

    virtual bool IsEnd ();
	virtual void Update ();
    virtual void Render () const;
};

}; // particle

#endif //__PIRANHA_PARTICLE_TRAIL_H__
