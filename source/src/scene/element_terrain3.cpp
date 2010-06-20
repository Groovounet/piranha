//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-29-2004
//! \file ./scene/element_terrain3.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_terrain3.h"
#include "../gl/index.h"

using namespace scene;

static const float      TIME =                  5.f;

CTerrain3::CTerrain3 ()
{
    m_pTerrain = 0;
    m_pFade1 = 0;
}

CTerrain3::~CTerrain3 ()
{
    terrain::CTerrain::Delete (m_pTerrain);
    if (m_pFade1)
        delete m_pFade1;
}

bool CTerrain3::Load ()
{
    m_pTerrain = terrain::CTerrain::Create ();

    m_pFade1 = new gl::CFade;
    m_pFade1->Fade (gl::FADE_OUT);
    m_pFade1->Color (gtl::CColor3<float> (1.0f, 1.0f, 1.0f));
    m_pFade1->Init ();

    return true;
}

void CTerrain3::Begin ()
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

void CTerrain3::End ()
{
	glDisable (GL_LIGHT0);
    glPopAttrib ();
}

bool CTerrain3::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTerrain3::Update ()
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

    m_pTerrain->Update ();

    if (fTime < 1.0f)
        m_pFade1->Times (0.0f, 0.5f);
    else if (fTime < 2.0f)
        m_pFade1->Times (1.0f, 1.5f);
    else if (fTime < 3.0f)
        m_pFade1->Times (2.0f, 2.5f);
    else if (fTime < 4.0f)
        m_pFade1->Times (3.0f, 3.5f);
    else if (fTime < 5.0f)
        m_pFade1->Times (4.0f, 4.5f);
}

void CTerrain3::Render () const
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

    if (util::CStateMachine::Instance ()->Enabled (util::ENABLED_PAUSE))
    {
        gl::CCamera::Instance ()->LookAt ();
    }
    else
    {
        if (fTime < 1.0f)
            gluLookAt (64, 96, 64, 128, 0, 48, 0, 0, 1);
        else if (fTime < 2.0f)
            gluLookAt (-128, 0, 96, 0, 0, 64, 0, 0, 1);
        else if (fTime < 3.0f)
            gluLookAt (0, 128, 96, 0, 0, 64, 0, 0, 1);
        else if (fTime < 4.0f)
            gluLookAt (128, 0, 96, 0, 0, 64, 0, 0, 1);
        else if (fTime < 5.0f)
            gluLookAt (0, 32, 128, 0, 64, 96, 0, 0, 1);
    }

    glLightfv (GL_LIGHT0, GL_POSITION, gtl::CVector4<float> (256.0f, 256.0f, 128.0f, 1.0f));

    glEnable (GL_DEPTH_TEST);
        glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
        m_pTerrain->Render ();
    glDisable (GL_DEPTH_TEST);

    m_pFade1->Render (fTime);
}

EType CTerrain3::Type ()
{
    return TYPE_TERRAIN3;
}

bool CTerrain3::HUD ()
{
    return true;
}
