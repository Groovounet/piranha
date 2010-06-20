//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-23-2004
//! \file ./particle/explode.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_PARTICLE_EXPLODE_H__
#define __PIRANHA_PARTICLE_EXPLODE_H__

#include "./system.h"
#include "./manager.h"
#include "../util/index.h"
#include "../file/texture.h"

namespace particle {

class CExplode : public CSystem
{
    friend CExplode* CManager::CreateExplode ();

    typedef struct SParticle
    {
	    float m_fTimeLife;
	    gtl::CVector3<float> m_SpeedI;
	    gtl::CVector3<float> m_AccelerationI;
        gtl::CVector3<float> m_PositionF;
        gtl::CColor4<float> m_Color;
    } TParticle;

private:
	float m_fParticleSize;
    gtl::CVector3<float> m_Position;
	float m_fStrength;
    unsigned int m_uiParticle;
    float m_fTimeLife;
    gtl::CColor4<float> m_Color;
    float m_fTimeStart;

    TParticle* m_pParticle;
    file::CTexture* m_pTexture;

    CExplode ();
    virtual ~CExplode ();

    void _Init ();

public:
	static const CExplode* Create (
        float fParticleSize, 
        const gtl::CVector3<float> & Position, 
        float fStrength,
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

#endif //__PIRANHA_PARTICLE_EXPLODE_H__
