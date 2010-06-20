//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-24-2004
//! \file ./particle/system_stars.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_PARTICLE_STARS_H__
#define __PIRANHA_PARTICLE_STARS_H__

#include "./system.h"
#include "./manager.h"
#include "../util/index.h"
#include "../file/texture.h"

namespace particle {

class CStars : public CSystem
{
    friend CStars* CManager::CreateStars ();

    typedef struct SParticle
    {
        gtl::CVector3<float> m_Position;
        gtl::CColor4<float> m_Color;
    } TParticle;

private:
	float m_fParticleSize;
    gtl::CVector3<float> m_Position;
    float m_fRadius;
    unsigned int m_uiParticle;
    float m_fTimeLife;
    float m_fTimeStart;

    TParticle* m_pParticle;
    file::CTexture* m_pTexture;

    CStars ();
    virtual ~CStars ();

    void _Init ();

public:
	static const CStars* Create (
        float fParticleSize, 
        const gtl::CVector3<float> & Position,
        float fRadius,
        unsigned int uiParticle);
    virtual bool IsEnd ();
	virtual void Update ();
    virtual void Render () const;
};

}; // particle

#endif //__PIRANHA_PARTICLE_STARS_H__
