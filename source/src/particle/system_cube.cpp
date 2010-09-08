//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-13-2004
//! \file ./particle/system_cube.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./system_cube.h"
#include "./manager.h"
#include "../util/timer_global.h"
#include <math.h>

using namespace particle;

CCube::CCube ()
{
    m_pPlane = 0;
    m_pParticle = 0;
    m_fTimeBlend = 0;
}

CCube::~CCube ()
{
    TParticle* pParticle = m_pParticle;
    TParticle* pParticleTemp = 0;

    while (pParticle)
    {
        pParticleTemp = pParticle;
        pParticle = pParticle->m_pNext;
        delete pParticleTemp;
    }
    
    delete m_pObject1;
    delete m_pObject2;
    delete m_pObject3;
	if(m_pPlane != 0)
		delete m_pPlane;

    m_pParticle = 0;
}

CCube* CCube::Create (
    const gtl::CVector3<float> & Position,
    float fSpeedNorm,
    float fAccuracy,
    float fTimeLife,
    float fTimeParticle,
    float fInterval)
{
    CCube* pSystem = CManager::Instance ()->CreateCube ();

    pSystem->m_Position = Position;
    pSystem->m_fSpeedNorm = fSpeedNorm;
    pSystem->m_fAccuracy = fAccuracy;
    pSystem->m_fTimeLife = fTimeLife;
    pSystem->m_fInterval = fInterval;
    pSystem->m_fTimeParticle = fTimeParticle;
    pSystem->m_fTimeStart = pSystem->m_fIntervalStart = util::CTimerGlobal::Instance ()->Time ();

    float fAngle = gtl::CRand::Float (0, 360.f);
    float fNorm = gtl::CRand::Float (0, pSystem->m_fAccuracy);
    pSystem->m_pParticle = new TParticle;
    pSystem->m_pParticle->m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();
    pSystem->m_pParticle->m_Speed = gtl::CVector3<float> (0, -pSystem->m_fSpeedNorm, 0);
    pSystem->m_pParticle->m_Speed (gtl::X) = cosf (fAngle) * fNorm;
    pSystem->m_pParticle->m_Speed (gtl::Z) = sinf (fAngle) * fNorm;
    pSystem->m_pParticle->m_Rotate = gtl::CVector3<float> (gtl::CRand::Float (-80.f, 80.f), gtl::CRand::Float (-80.f, 80.f), gtl::CRand::Float (-80.f, 80.f));
    pSystem->m_pParticle->m_pNext = 0;

    pSystem->m_pObject1 = new gl::CObjectDL;
    pSystem->m_pObject1->Cube (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (1, 1, 1));
    pSystem->m_pObject2 = new gl::CObjectDL;
    pSystem->m_pObject2->Cube (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (2, 2, 2));
    pSystem->m_pObject3 = new gl::CObjectDL;
    pSystem->m_pObject3->Plane (gtl::CVector3<float> (0, 0, 0), gtl::CVector2<float> (1, 1), gtl::CVector2<float> (1, 1));

    return pSystem;
}

void CCube::Render () const
{
    TParticle* pParticle = m_pParticle;
    while (pParticle)
    {
        if (m_fTimeCurrent - pParticle->m_fTimeStart < m_fTimeParticle)
        {
            gtl::CVector3<float> Position = pParticle->m_Speed * (m_fTimeCurrent - pParticle->m_fTimeStart) * 1.0f + m_Position;
            glPushMatrix ();
                glTranslatef (Position (gtl::X), Position (gtl::Y), Position (gtl::Z));
                glRotatef (pParticle->m_Rotate (gtl::X) * m_fTimeCurrent, 1, 0, 0);
                glRotatef (pParticle->m_Rotate (gtl::Y) * m_fTimeCurrent, 0, 1, 0);
                glRotatef (pParticle->m_Rotate (gtl::Z) * m_fTimeCurrent, 0, 0, 1);
                glEnable (GL_CULL_FACE);
                    m_pObject1->Render ();
                glDisable (GL_CULL_FACE);
		        glEnable (GL_BLEND);
			    glDepthMask (GL_FALSE);
                    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glColor4f (1.0f, 1.0f, 1.0f, MIN (1.0f - (m_fTimeCurrent - pParticle->m_fTimeStart) / (m_fTimeParticle * 1), 1.0f));
                    m_pObject2->Render ();
			    glDepthMask (GL_TRUE);
		        glDisable (GL_BLEND);
            glPopMatrix ();
        }

        pParticle = pParticle->m_pNext;
    }

    if (m_pPlane)
    {
        if (m_PlanePosition (gtl::Y) > 0)
        {
            glPushMatrix ();
                glTranslatef (m_PlanePosition (gtl::X), m_PlanePosition (gtl::Y), m_PlanePosition (gtl::Z));
                glRotatef (m_pPlane->m_Rotate (gtl::X), 1, 0, 0);
                glRotatef (m_pPlane->m_Rotate (gtl::Y), 0, 1, 0);
                glRotatef (m_pPlane->m_Rotate (gtl::Z), 0, 0, 1);
                glEnable (GL_CULL_FACE);
                    m_pObject3->Render ();
                glDisable (GL_CULL_FACE);
            glPopMatrix ();
        }
        else
        {
            glPushMatrix ();
                glRotatef (m_pPlane->m_Rotate (gtl::X), 1, 0, 0);
                glRotatef (m_pPlane->m_Rotate (gtl::Y), 0, 1, 0);
                glRotatef (m_pPlane->m_Rotate (gtl::Z), 0, 0, 1);
                glEnable (GL_BLEND);
                glEnable (GL_CULL_FACE);
                    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glColor4f (1.0f, 1.0f, 1.0f, MIN (1.0f - (m_fTimeCurrent - m_fTimeBlend) / 2, 1.0f));
                    m_pObject3->Render ();
                glDisable (GL_CULL_FACE);
                glDisable (GL_BLEND);
            glPopMatrix ();          
        }
    }
}

void CCube::Update ()
{
    m_fTimeCurrent = util::CTimerGlobal::Instance ()->Time ();

    if (m_pPlane)
    {
        m_PlanePosition = m_pPlane->m_Speed * (m_fTimeCurrent - m_pPlane->m_fTimeStart) * 1.0f + m_Position;
        if (!m_fTimeBlend)
            m_fTimeBlend = m_fTimeCurrent + m_fTimeLife * 0.9f;
    }

    // 11-12-2004 - NOTE : Delete particles that lifes are end.
    if ((m_fTimeCurrent - m_fTimeStart) > (m_fTimeLife - m_fTimeParticle))
    {
        if (!m_pPlane)
        {
            m_pPlane = new TParticle;
            m_pPlane->m_fTimeStart = m_fTimeCurrent;
            m_pPlane->m_Rotate = gtl::CVector3<float> (90, 0, 0);
            m_pPlane->m_Speed = gtl::CVector3<float> (0, -m_fSpeedNorm, 0);
            m_pPlane->m_pNext = 0;
        }
        return;
    }

    if (m_fTimeCurrent - m_fIntervalStart > m_fInterval)
    {
        m_fIntervalStart = m_fTimeCurrent;

        TParticle* pParticleLast = m_pParticle;
        while (pParticleLast->m_pNext)
            pParticleLast = pParticleLast->m_pNext;

        float fAngle = gtl::CRand::Float (0, 360.f);
        float fNorm = gtl::CRand::Float (m_fAccuracy / 4.f, m_fAccuracy);

        pParticleLast->m_pNext = new TParticle;
        pParticleLast->m_pNext->m_fTimeStart = m_fTimeCurrent;
        pParticleLast->m_pNext->m_Speed = gtl::CVector3<float> (0, -m_fSpeedNorm, 0);
        pParticleLast->m_pNext->m_Speed (gtl::X) = cosf (fAngle) * fNorm;
        pParticleLast->m_pNext->m_Speed (gtl::Z) = sinf (fAngle) * fNorm;
        pParticleLast->m_pNext->m_Rotate = gtl::CVector3<float> (gtl::CRand::Float (-80.f, 80.f), gtl::CRand::Float (-80.f, 80.f), gtl::CRand::Float (-80.f, 80.f));
        pParticleLast->m_pNext->m_pNext = 0;
    }
}

bool CCube::IsEnd ()
{
    return false;
}
