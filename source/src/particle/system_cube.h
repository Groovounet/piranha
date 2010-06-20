//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-13-2004
//! \file ./particle/cube.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_PARTICLE_CUBE_H__
#define __PIRANHA_PARTICLE_CUBE_H__

#include "../util/common.h"
#include "../gl/object_dl.h"
#include "./system.h"
#include "./manager.h"

namespace particle {

class CCube : public CSystem
{
	friend CCube* CManager::CreateCube ();

    typedef struct SParticle
    {
        SParticle* m_pNext;
        float m_fTimeStart;
        gtl::CVector3<float> m_Speed;
        gtl::CVector3<float> m_Rotate;
    } TParticle;

private:
    gtl::CVector3<float> m_Position;
    gtl::CVector3<float> m_PlanePosition;
    float m_fTimeCurrent;
    float m_fSpeedNorm;
    float m_fTimeLife;
    float m_fTimeStart;
    float m_fTimeParticle;
    float m_fTimeBlend;
    float m_fInterval;
    float m_fIntervalStart;
    float m_fAccuracy;
    TParticle* m_pParticle;
    TParticle* m_pPlane;
    unsigned int m_uiParticle;
    gl::CObjectDL* m_pObject1;
    gl::CObjectDL* m_pObject2;
    gl::CObjectDL* m_pObject3;

    CCube ();
    virtual ~CCube ();

public:
    static CCube* Create (const gtl::CVector3<float> & Position, float fSpeedNorm, float fAccuracy, float fTimeLife, float fTimeParticle, float fInterval);

    virtual bool IsEnd ();
    virtual void Render () const;
    virtual void Update ();
};

}; // particle

#endif //__PIRANHA_PARTICLE_CUBE_H__
