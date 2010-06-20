//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-26-2004
//! \file ./scene/element_tunnel1.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_tunnel1.h"
#include "../particle/index.h"

using namespace scene;

namespace scene 
{
    static const float      TIME =                  2.5f;
    static const float      SEGMENTS =              24.f;
    static const float      SIZE =                  16.f;
    static const float      MOVE_SPEED1 =           0.2f;
    static const float      MOVE_SPEED2 =           0.5f;
    static const float      TEXTURE_SPEED =         240.f;
    static const float      TEXTURE_DETAIL_X =      1.0f;
    static const float      TEXTURE_DETAIL_Y =      4.0f;
    static const float      TEXTURE_WRAPPING =      2.0f;
    static const char*      TEXTURE_TUNNEL =        "./data/tunnel2.tga";
    static const char*      TEXTURE_COLORMAP =      "./data/planet/colormap1.tga";
    static const char*      TEXTURE_CLOUDS =        "./data/planet/clouds1.tga";
};

CTunnel1::CTunnel1 ()
{

}

CTunnel1::~CTunnel1 ()
{
    file::CManager* pManager = file::CManager::Instance ();

    pManager->DeleteTexture2D (m_pTextureTunnel);
    pManager->DeleteTexture2D (m_pTexturePlanet);
    pManager->DeleteTexture2D (m_pTextureClouds);

    delete m_pFade1;
}

bool CTunnel1::Load ()
{
    file::CManager* pManager = file::CManager::Instance ();

    m_pTextureTunnel = pManager->CreateTexture2D (TEXTURE_TUNNEL);
    m_pTexturePlanet = pManager->CreateTexture2D (TEXTURE_COLORMAP);
    m_pTextureClouds = pManager->CreateTexture2D (TEXTURE_CLOUDS);

    m_pFade1 = new gl::CFade;
    m_pFade1->Times (0.0f, 1.f);
    m_pFade1->Fade (gl::FADE_OUT);
    m_pFade1->Color (gtl::CColor3<float> (0.0f, 0.0f, 0.0f));
    m_pFade1->Init ();

    return true;
}

void CTunnel1::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    glShadeModel (GL_SMOOTH);
    glClearColor (0.0f, 0.0f, 0.1f, 0.0f);

    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->SetViewDistance (512.f);
    pCamera->Init (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (0, 1, 0));
    pCamera->Move (-2.0f);

    particle::CStars::Create (
        3.f, 
        gtl::CVector3<float> (0, 0, 0), 
        256.f,
        2048);
}

void CTunnel1::End ()
{
    gl::CCamera::Kill ();
}

bool CTunnel1::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTunnel1::Update ()
{
    particle::CManager::Instance ()->Update ();
}

void CTunnel1::Render () const
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

    gl::CCamera::Instance ()->LookAt ();

    glEnable (GL_DEPTH_TEST);
    glDepthMask (GL_FALSE);
        particle::CManager::Instance ()->Render ();
    glDepthMask (GL_TRUE);
    glDisable (GL_DEPTH_TEST);

    _RenderTunnel (fTime);
    m_pFade1->Render (fTime);
}

EType CTunnel1::Type ()
{
    return TYPE_TUNNEL1;
}

bool CTunnel1::HUD ()
{
    return true;
}

void CTunnel1::_RenderTunnel (float fTime) const
{
    gl::CStateAuto<GL_BLEND> Enable;
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTextureARB (GL_TEXTURE0_ARB);
	glEnable (GL_TEXTURE_2D);
	m_pTextureTunnel->Bind ();

    glPushMatrix ();
        glTranslatef (0, -3, 0);
        glBegin (GL_QUADS);
            float fInc = 360.0f / SEGMENTS;
            for (float p = 0.0f; p < 360.0f; p += fInc * 1.f)
            {    
                float x1 = sinf (p * (float)PI / 180.0f);
                float y1 = cosf (p * (float)PI / 180.0f);
                float x2 = sinf ((p + fInc) * (float)PI / 180.0f);
                float y2 = cosf ((p + fInc) * (float)PI / 180.0f);
                
                float u1 = (p * TEXTURE_WRAPPING) / 360.0f;
                float u2 = ((p + fInc) * TEXTURE_WRAPPING) / 360.0f;
                float v1 = (0.0f * TEXTURE_WRAPPING) / (float)scene::SIZE;
                float v2 = (SIZE * TEXTURE_WRAPPING) / (float)scene::SIZE;

                v1 += fTime * 2.0f;
                v2 += fTime * 2.0f;

                float fColor1 = 0.5f * fTime / TIME;
                float fColor2 = 0.0f;
                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u1 * TEXTURE_DETAIL_X, v1 * TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor1); 
                glVertex3f (x1, 0.0f, y1);

                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u1 * TEXTURE_DETAIL_X, v2 * TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor2); 
                glVertex3f (x1, SIZE, y1);

                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u2 * TEXTURE_DETAIL_X, v2 * TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor2); 
                glVertex3f (x2, SIZE, y2);

                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u2 * TEXTURE_DETAIL_X, v1 * TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor1); 
                glVertex3f (x2, 0.0f, y2);
            }
        glEnd ();
    glPopMatrix ();

	glActiveTextureARB (GL_TEXTURE0_ARB);
	glDisable (GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, 0);
}
