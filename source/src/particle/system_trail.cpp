//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-26-2004
//! \file ./particle/system_trail.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./system_trail.h"
#include "../gl/index.h"

using namespace particle;

static const char*      TEXTURE_PARTICLE =      "./data/particle/particle1.tga";

CTrail::CTrail ()
{
    m_pParticleFirst = 0;
    m_pParticleLast = 0;
    m_fTimeCreated = 0.f;
    m_fTimeInterval = 0.05f;

    m_pTexture = file::CManager::Instance ()->CreateTexture2D (TEXTURE_PARTICLE);
}

CTrail::~CTrail ()
{
    file::CManager::Instance ()->DeleteTexture2D (m_pTexture);

    TParticle* pParticle = m_pParticleFirst;
    while (pParticle)
    {
        TParticle* pParticleTemp = pParticle;
        pParticle = pParticle->m_pNext;
        delete pParticleTemp;
    }
}

const CTrail* CTrail::Create (
    const gtl::CVector3<float> & Position,
    const gtl::CVector3<float> & Speed,
    const gtl::CVector3<float> & Acceleration,
    const gtl::CColor4<float> & Color,
    float fParticleSize, 
    float fTimeSystem,
    float fTimeParticle)
{
    CTrail* pSystem = CManager::Instance ()->CreateTrail ();
	if (!pSystem)
		return 0;

	pSystem->m_Position = Position;
    pSystem->m_Speed = Speed;
    pSystem->m_Acceleration = Acceleration;
    pSystem->m_Color = Color;
	pSystem->m_fParticleSize = fParticleSize;
    pSystem->m_fTimeSystem = fTimeSystem;
    pSystem->m_fTimeParticle = fTimeParticle;
    pSystem->_Init ();

	return pSystem;
}

void CTrail::Render () const
{
	glEnable (m_uiPointSprite);
    glEnable (GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glEnable (GL_CULL_FACE);

	glTexEnvf (GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);

	m_pTexture->Bind ();

    glPointSize (m_fParticleSize);
    glPointParameterfvARB (GL_POINT_DISTANCE_ATTENUATION_ARB, gtl::CVector3<float>(0.0f, 1.0f, 0.0f));

    glBegin (GL_POINTS);
        TParticle* pParticle = m_pParticleFirst;
        while (pParticle)
        {
            glColor4fv (pParticle->m_Color);
		    glVertex3fv (pParticle->m_Position);

            pParticle = pParticle->m_pNext;
        }
	glEnd ();

	glDisable (GL_CULL_FACE);
	glDisable (GL_BLEND);
	glDisable (GL_TEXTURE_2D);
	glDisable (m_uiPointSprite);
}

void CTrail::Update ()
{
    float fTime = util::CTimerGlobal::Instance ()->Time ();

    TParticle* pParticle = m_pParticleFirst;
    while (pParticle)
    {
        if (fTime - pParticle->m_fTimeStart > m_fTimeParticle)
        {
            m_pParticleFirst = pParticle->m_pNext;
            delete pParticle;
            pParticle = m_pParticleFirst;
            continue;
        }

        pParticle->m_Color (gtl::A) = 1.0f - ((fTime - pParticle->m_fTimeStart) / m_fTimeParticle);
        pParticle = pParticle->m_pNext;
    }

    if (fTime - m_fTimeStart > m_fTimeSystem - m_fTimeParticle)
        return;

    if (fTime - m_fTimeCreated > m_fTimeInterval)// && (fTime - m_fTimeStart < m_fTimeSystem - m_fTimeParticle))
    {
        m_fTimeCreated = fTime;

        TParticle* pParticle = m_pParticleFirst;
        if (!pParticle)
        {
            pParticle = new TParticle;
            m_pParticleLast = m_pParticleFirst = pParticle;
        }
        else
        {
            while (pParticle->m_pNext)
                pParticle = pParticle->m_pNext;
            pParticle->m_pNext = new TParticle;
            pParticle = pParticle->m_pNext;
        }
        pParticle->m_fTimeStart = fTime;
        pParticle->m_Position = m_Acceleration * 0.5 * SQR (fTime - m_fTimeStart) + m_Speed * (fTime - m_fTimeStart) + m_Position;
        pParticle->m_Color = m_Color;
        pParticle->m_pNext = 0;
    }
}

bool CTrail::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > m_fTimeSystem;
}

void CTrail::_Init ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();
}
