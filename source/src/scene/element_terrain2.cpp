//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./scene/element_terrain2.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_terrain2.h"
#include "../gl/index.h"

using namespace scene;

static const float      TIME =                  5.f;

CTerrain2::CTerrain2 ()
{
    m_pTerrain = 0;
}

CTerrain2::~CTerrain2 ()
{
    terrain::CTerrain::Delete (m_pTerrain);
}

bool CTerrain2::Load ()
{
    m_pTerrain = terrain::CTerrain::Create ();
    return true;
}

void CTerrain2::Begin ()
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

void CTerrain2::End ()
{
	glDisable (GL_LIGHT0);
    glPopAttrib ();
}

bool CTerrain2::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTerrain2::Update ()
{
    m_pTerrain->Update ();
}

void CTerrain2::Render () const
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

    gl::CCamera::Instance ()->LookAt ();

    glLightfv (GL_LIGHT0, GL_POSITION, gtl::CVector4<float> (256.0f, 256.0f, 128.0f, 1.0f));

    glEnable (GL_DEPTH_TEST);
        glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
        m_pTerrain->Render ();
    glDisable (GL_DEPTH_TEST);
}

EType CTerrain2::Type ()
{
    return TYPE_TERRAIN2;
}

bool CTerrain2::HUD ()
{
    return true;
}
