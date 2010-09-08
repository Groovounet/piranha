//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-23-2004
//! \file ./scene/element_explode3.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_explode3.h"
#include "../particle/index.h"

using namespace scene;

static const float      TIME =                  5.f;
static const char*      TEXTURE_FADE1 =         "./data/fade3.tga";

CExplode3::CExplode3 ()
{

}

CExplode3::~CExplode3 ()
{
    file::CManager* pManager = file::CManager::Instance ();
    pManager->DeleteTexture2D (m_pTextureFade1);

    delete m_pFade1;
}

bool CExplode3::Load ()
{
    file::CManager* pManager = file::CManager::Instance ();
    m_pTextureFade1 = pManager->CreateTexture2D (TEXTURE_FADE1);

    m_pFade1 = new gl::CFade;
    m_pFade1->Times (0.0f, 2.5f);
    m_pFade1->TextureActive (gl::TEXTURE0);
    m_pFade1->Fade (gl::FADE_OUT);
    m_pFade1->Color (gtl::CColor3<float> (1.0f, 1.0f, 1.0f));
    m_pFade1->Init ();

    return true;
}

void CExplode3::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();
    m_fTimeExplode = 0.f;

    particle::CDeathPlanet::Create (48.f, gtl::CVector3<float> (0,0,0), 1.5f, 1024, TIME - 1.f, gtl::CColor4<float> (1.0f, 0.5f, 0.2f, 1.0f));

    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->Enable (gl::CAMERA_FRUSTUM);
    pCamera->SetViewDistance (256.f);
    pCamera->Init (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (0, 0.1f, 0));
    pCamera->Move (-40.f);

    glPushAttrib (GL_ALL_ATTRIB_BITS);

    glShadeModel (GL_SMOOTH);
    glClearColor (0.0f, 0.0f, 0.1f, 0.0f);

	float Ambient[] = {0.3f, 0.3f, 0.3f, 0.3f};
	float Diffuse[] = {0.9f, 0.9f, 0.9f, 0.9f};
	float Specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glLightfv (GL_LIGHT0, GL_AMBIENT, Ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, Diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, Specular);

	glEnable (GL_LIGHT0);
    glClearStencil (0x0);
}

void CExplode3::End ()
{
    particle::CManager::Instance ()->Clean ();
	particle::CManager::Kill();

    glDisable (GL_LIGHT0);
    glPopAttrib ();

    gl::CCamera::Kill ();
}

bool CExplode3::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CExplode3::Update ()
{
    particle::CManager::Instance ()->Update ();
}

void CExplode3::Render () const
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

    SDL_WarpMouse (WINDOW_WIDTH >> 1, WINDOW_HEIGHT >> 1);
    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->LookAt ();

    glPushMatrix ();
        glRotatef (15.f, 0, 1, 0);

        float Position[] = {0.0f, -1.0f, 0.0f, 0.0f};
        glLightfv (GL_LIGHT0, GL_POSITION, Position);

        glRotatef (15.f, 1, 0, 0);
        glRotatef (60.f + fTime * 36, 0, 0, 1);

        glEnable (GL_DEPTH_TEST);
            glDepthMask (GL_FALSE);
                particle::CManager::Instance ()->Render ();
            glDepthMask (GL_TRUE);
        glDisable (GL_DEPTH_TEST);
    glPopMatrix ();

    if (fTime < 2.5f)
    {
        //m_pTextureFade1->Bind ();
        //glEnable (GL_TEXTURE_2D);
            m_pFade1->Render (fTime);
        //glDisable (GL_TEXTURE_2D);
    }
}

EType CExplode3::Type ()
{
    return TYPE_EXPLODE3;
}

bool CExplode3::HUD ()
{
    return true;
}
