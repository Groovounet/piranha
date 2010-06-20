//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./scene/element_author.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_author.h"
#include "../particle/index.h"

using namespace scene;

static const float      TIME =                  10.f;
static const char*      TEXTURE_AUTHOR =      "./data/g-truc.tga";

CAuthor::CAuthor ()
{

}

CAuthor::~CAuthor ()
{
    file::CManager::Instance ()->DeleteTexture2D (m_pTexture);
}

bool CAuthor::Load ()
{
    m_pTexture = file::CManager::Instance ()->CreateTexture2D (TEXTURE_AUTHOR);
    if (!m_pTexture)
        return false;
    
    return true;
}

void CAuthor::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    particle::CCube::Create (
        gtl::CVector3<float> (0, 128, 0),
        32.f,
        0.5f,
        6.0f,
        4.0f,
        0.05f);

    glClearColor (1.0, 1.0, 1.0, 1.0);
    glShadeModel (GL_FLAT);
}

void CAuthor::End ()
{
    glDeleteTextures (1, &m_uiTextureMotionBlur);
    particle::CManager::Instance ()->Clean ();
}

void CAuthor::Update ()
{
    particle::CManager::Instance ()->Update ();
}

void CAuthor::Render () const
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	gluLookAt (0.0f, -0.9f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    glEnable (GL_DEPTH_TEST);
    glEnable (GL_TEXTURE_2D);
        glPushMatrix ();
            m_pTexture->Bind ();
            particle::CManager::Instance ()->Render ();
	    glPopMatrix ();
    glDisable (GL_TEXTURE_2D);
    glDisable (GL_DEPTH_TEST);
}

bool CAuthor::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

EType CAuthor::Type ()
{
    return TYPE_AUTHOR;
}

bool CAuthor::HUD ()
{
    return false;
}

