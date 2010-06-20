//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-24-2004
//! \file ./particle/system_stars.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./system_stars.h"
#include "../util/timer_global.h"
#include "../file/manager.h"
#include "../gl/index.h"

using namespace particle;

static const char*      TEXTURE_PARTICLE =      "./data/particle/particle1.tga";

CStars::CStars ()
{
    m_pParticle = 0;

    file::CManager* pManager = file::CManager::Instance ();
    m_pTexture = pManager->CreateTexture2D (TEXTURE_PARTICLE);
}

CStars::~CStars ()
{
    file::CManager* pManager = file::CManager::Instance ();
    pManager->DeleteTexture2D (m_pTexture);

    if (m_pParticle)
        delete [] m_pParticle;
}

const CStars* CStars::Create (
        float fParticleSize, 
        const gtl::CVector3<float> & Position, 
        float fRadius,
        unsigned int uiParticle)
{
	CStars* pSystem = CManager::Instance ()->CreateStars ();
	if (pSystem == 0)
		return 0;

	pSystem->m_fParticleSize = fParticleSize;
	pSystem->m_Position = Position;
    pSystem->m_fRadius = fRadius;
    pSystem->m_uiParticle = uiParticle;
    pSystem->_Init ();

	return pSystem;
}

void CStars::_Init ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    m_pParticle = new TParticle [m_uiParticle];
	for (unsigned int i = 0; i < m_uiParticle; i++)
	{
        float fRandAngleA = gtl::CRand::Float (0.f, (float)PI);
        float fRandAngleB = gtl::CRand::Float (0.f, 2.f * (float)PI);
		float fRandCosA = cos (fRandAngleA);
		float fRandSinA = sin (fRandAngleA);
		float fRandCosB = cos (fRandAngleB);
		float fRandSinB = sin (fRandAngleB);
        gtl::CVector3<float> Position (
            fRandSinA * fRandCosB * m_fRadius,
            fRandSinA * fRandSinB * m_fRadius,
            fRandCosA * m_fRadius);
        gtl::CColor4<float> Color (
            gtl::CRand::Float (0.7f, 1.0f),
            gtl::CRand::Float (0.7f, 1.0f),
            gtl::CRand::Float (0.7f, 1.0f),
            gtl::CRand::Float (0.5f, 1.0f));
        m_pParticle[i].m_Position = m_Position + Position;
        m_pParticle[i].m_Color = Color;
    }
}

void CStars::Update ()
{

}

void CStars::Render () const
{
	glEnable (GL_TEXTURE_2D);
	glEnable (m_uiPointSprite);
	glEnable (GL_BLEND);
	glEnable (GL_CULL_FACE);

	glTexEnvf (GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);

	m_pTexture->Bind ();

    glPointSize (m_fParticleSize);
    glPointParameterfvARB (GL_POINT_DISTANCE_ATTENUATION_ARB, gtl::CVector3<float>(1.0f, 0.0f, 0.0f));

    glBegin (GL_POINTS);
	    for (unsigned int i = 0; i < m_uiParticle; i++)
	    {
		    glColor4fv (m_pParticle[i].m_Color);
		    glVertex3fv (m_pParticle[i].m_Position);
	    }
	glEnd ();

	glDisable (GL_CULL_FACE);
	glDisable (GL_BLEND);
	glDisable (m_uiPointSprite);
	glDisable (GL_TEXTURE_2D);
}

bool CStars::IsEnd ()
{
    return false;//util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > m_fTimeLife;
}
