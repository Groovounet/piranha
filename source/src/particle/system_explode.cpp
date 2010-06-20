//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-23-2004
//! \file ./particle/system_explode.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./system_explode.h"
#include "../util/index.h"
#include "../file/index.h"
#include "../gl/index.h"

using namespace particle;

static const char*      TEXTURE_PARTICLE =      "./data/particle/particle1.tga";

CExplode::CExplode ()
{
    m_pParticle = 0;

    file::CManager* pManager = file::CManager::Instance ();
    m_pTexture = pManager->CreateTexture2D (TEXTURE_PARTICLE);
}

CExplode::~CExplode ()
{
    file::CManager* pManager = file::CManager::Instance ();
    pManager->DeleteTexture2D (m_pTexture);

    if (m_pParticle)
        delete [] m_pParticle;
}

const CExplode* CExplode::Create (
        float fParticleSize, 
        const gtl::CVector3<float> & Position, 
        float fStrength,
        unsigned int uiParticle,
        float fTimeLife, 
        const gtl::CColor4<float> & Color)
{
	CExplode* pSystem = CManager::Instance ()->CreateExplode ();
	if (pSystem == 0)
		return 0;

	pSystem->m_fParticleSize = fParticleSize;
	pSystem->m_Position = Position;
    pSystem->m_fStrength = fStrength;
    pSystem->m_uiParticle = uiParticle;
    pSystem->m_fTimeLife = fTimeLife;
	pSystem->m_Color = Color;
    pSystem->_Init ();

	return pSystem;
}

void CExplode::_Init ()
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
		float fRandStrength = m_fStrength * gtl::CRand::Float (0.9f, 1.0f);
        gtl::CVector3<float> Speed (
            fRandSinA * fRandCosB * fRandStrength,
            fRandSinA * fRandSinB * fRandStrength,
            fRandCosA * fRandStrength);
        gtl::CVector3<float> Acceleration (-Speed / 6.0f);
        m_pParticle[i].m_SpeedI = Speed;
        m_pParticle[i].m_AccelerationI = Acceleration;
        m_pParticle[i].m_fTimeLife = m_fTimeLife * gtl::CRand::Float (0.9f, 1.0f);
        m_pParticle[i].m_Color = m_Color;
    }
}
/*
void CExplode::End ()
{

}
   
bool CExplode::Load ()
{
    return true;
}
*/
void CExplode::Update ()
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

	for (unsigned int i = 0; i < m_uiParticle; i++)
	{
        m_pParticle[i].m_Color (gtl::A) = 1 - fTime / m_fTimeLife;
        m_pParticle[i].m_PositionF = m_pParticle[i].m_AccelerationI * 0.5f * SQR (fTime) + m_pParticle[i].m_SpeedI * fTime + m_Position;
    }
}

void CExplode::Render () const
{
	glEnable (GL_TEXTURE_2D);
	glEnable (m_uiPointSprite);
	glEnable (GL_BLEND);
	glEnable (GL_CULL_FACE);

	glTexEnvf (GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);

	m_pTexture->Bind ();

    glPointSize (m_fParticleSize);
    glPointParameterfvARB (GL_POINT_DISTANCE_ATTENUATION_ARB, gtl::CVector3<float>(0.01f, 0.0f, 0.0f));

	glBegin (GL_POINTS);
	    for (unsigned int i = 0; i < m_uiParticle; i++)
	    {
		    glColor4fv (m_pParticle[i].m_Color);
		    glVertex3fv (m_pParticle[i].m_PositionF);
	    }
	glEnd ();

	glDisable (GL_CULL_FACE);
	glDisable (GL_BLEND);
	glDisable (m_uiPointSprite);
	glDisable (GL_TEXTURE_2D);
}

bool CExplode::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > m_fTimeLife;
}
