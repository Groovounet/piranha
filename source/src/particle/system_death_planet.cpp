//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-23-2004
//! \file ./particle/system_death_planet.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./system_death_planet.h"
#include "../util/timer_global.h"
#include "../file/manager.h"
#include "../gl/proc.h"

using namespace particle;

static const char*      TEXTURE_PARTICLE =      "./data/particle/particle2.tga";

CDeathPlanet::CDeathPlanet ()
{
    m_pParticle = 0;
    file::CManager* pManager = file::CManager::Instance ();
    m_pTexture = pManager->CreateTexture2D (TEXTURE_PARTICLE);
}

CDeathPlanet::~CDeathPlanet ()
{
    file::CManager* pManager = file::CManager::Instance ();
    pManager->DeleteTexture2D (m_pTexture);

    if (m_pParticle)
        delete [] m_pParticle;
}

const CDeathPlanet* CDeathPlanet::Create (
        float fParticleSize, 
        const gtl::CVector3<float> & Position,
        float fRadius,
        unsigned int uiParticle,
        float fTimeLife, 
        const gtl::CColor4<float> & Color)
{
	CDeathPlanet* pSystem = CManager::Instance ()->CreateDeathPlanet ();
	if (pSystem == 0)
		return 0;

	pSystem->m_fParticleSize = fParticleSize;
	pSystem->m_Position = Position;
    pSystem->m_fRadius = fRadius;
    pSystem->m_uiParticle = uiParticle;
    pSystem->m_fTimeLife = fTimeLife;
	pSystem->m_Color = Color;
    pSystem->_Init ();

	return pSystem;
}

void CDeathPlanet::_Init ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    m_pParticle = new TParticle [m_uiParticle];
	for (unsigned int i = 0; i < m_uiParticle; i++)
	{
        float fRandAngleA = gtl::CRand::Float (0.f, (float)PI);
        float fRandAngleB = gtl::CRand::Float (0.f, 2.f * (float)PI);
		float fCosA = cos (fRandAngleA);
		float fSinA = sin (fRandAngleA);
		float fCosB = cos (fRandAngleB);
		float fSinB = sin (fRandAngleB);
		float fNorm = m_fRadius * gtl::CRand::Float (0.0f, 1.0f);
        gtl::CVector3<float> Position (
            fSinA * fCosB * fNorm,
            fSinA * fSinB * fNorm,
            fCosA * fNorm);
        m_pParticle[i].m_Color = m_Color;
        m_pParticle[i].m_Position = Position;
        m_pParticle[i].m_fTimeLife = m_fTimeLife * gtl::CRand::Float (0.9f, 1.0f);
    }
}
/*
void CDeathPlanet::End ()
{

}
   
bool CDeathPlanet::Load ()
{
    return true;
}
*/
void CDeathPlanet::Update ()
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

	for (unsigned int i = 0; i < m_uiParticle; i++)
        m_pParticle[i].m_Color (gtl::A) = 1 - fTime / m_pParticle[i].m_fTimeLife;
}

void CDeathPlanet::Render () const
{
	glEnable (m_uiPointSprite);
    glEnable (GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glEnable (GL_CULL_FACE);

	glTexEnvf (GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);

	m_pTexture->Bind ();
	glPointSize (m_fParticleSize);
	glBegin (GL_POINTS);
	    for (unsigned int i = 0; i < m_uiParticle; i++)
	    {
		    glColor4fv (m_pParticle[i].m_Color);
		    glVertex3fv (m_pParticle[i].m_Position);
	    }
	glEnd ();

	glDisable (GL_CULL_FACE);
	glDisable (GL_BLEND);
	glDisable (GL_TEXTURE_2D);
	glDisable (m_uiPointSprite);
}

bool CDeathPlanet::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > m_fTimeLife;
}
