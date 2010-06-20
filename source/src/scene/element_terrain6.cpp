//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./scene/element_terrain6.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_terrain6.h"
#include "../gl/index.h"
#include "../particle/index.h"

using namespace scene;

static const float      TIME =                  20.f;

CTerrain6::CTerrain6 ()
{
    m_pTerrain = 0;
    m_fTimeExplode = 0;
}

CTerrain6::~CTerrain6 ()
{
    terrain::CTerrain::Delete (m_pTerrain);
}

bool CTerrain6::Load ()
{
    m_pTerrain = terrain::CTerrain::Create ();

    return true;
}

void CTerrain6::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    glPushAttrib (GL_ALL_ATTRIB_BITS);

    glShadeModel (GL_SMOOTH);
    glClearColor (0.0f, 0.0f, 0.1f, 0.0f);

    glLightfv (GL_LIGHT0, GL_AMBIENT, gtl::CColor4<float>(0.3f, 0.3f, 0.3f, 0.3f));
	glLightfv (GL_LIGHT0, GL_DIFFUSE, gtl::CColor4<float>(0.9f, 0.9f, 0.9f, 0.9f));
	glLightfv (GL_LIGHT0, GL_SPECULAR, gtl::CColor4<float>(1.0f, 1.0f, 1.0f, 1.0f));

	glEnable (GL_LIGHT0);
}

void CTerrain6::End ()
{
	glDisable (GL_LIGHT0);
    glPopAttrib ();
}

bool CTerrain6::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTerrain6::Update ()
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

    particle::CManager::Instance ()->Update ();
    m_pTerrain->Update ();

    if (fTime > TIME - 0.5f)
        return;

    if (fTime - m_fTimeExplode > 0.02f)
    {
        m_fTimeExplode = fTime;
        for (int i = 0; i < (int)fTime; i++)
        {
            int x = gtl::CRand::Int (-256, 256);
            int y = gtl::CRand::Int (-256, 256);
            float fHeight = m_pTerrain->Distort (x, y);

            gtl::CVector3<float> Position = gtl::CVector3<float>((float)x, (float)y, fHeight);
            particle::CExplode::Create (
                48.f * fTime / TIME,
                Position, 
                24.f,
                8, 
                0.5f, 
                gtl::CColor4<float> (1.0f, 0.5f, 0.2f, 1.0f));
        }
    }
}

void CTerrain6::Render () const
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
    
    gl::CCamera::Instance ()->LookAt ();

    glLightfv (GL_LIGHT0, GL_POSITION, gtl::CVector4<float> (256.0f, 256.0f, 128.0f, 1.0f));
    glEnable (GL_DEPTH_TEST);
        glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
        m_pTerrain->Render ();

        glDepthMask (GL_FALSE);
            particle::CManager::Instance ()->Render ();
        glDepthMask (GL_TRUE);
    glDisable (GL_DEPTH_TEST);
}

EType CTerrain6::Type ()
{
    return TYPE_TERRAIN6;
}

bool CTerrain6::HUD ()
{
    return true;
}
