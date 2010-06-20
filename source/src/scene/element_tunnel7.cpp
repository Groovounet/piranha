//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-26-2004
//! \file ./scene/element_tunnel7.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_tunnel7.h"
#include "../particle/index.h"

using namespace scene;

namespace scene {
    static const float      TIME =                  5.f;
    static const float      DISPLACEMENT =          1.f;
    static const float      SEGMENTS =              24.f;
    static const float      CIRCLES =               16.f;
    static const float      MOVE_SPEED1 =           0.2f;
    static const float      MOVE_SPEED2 =           0.5f;
    static const float      TEXTURE_SPEED =         240.f;
    static const float      TEXTURE_DETAIL_X =      1.0f;
    static const float      TEXTURE_DETAIL_Y =      4.0f;
    static const float      TEXTURE_WRAPPING =      2.0f;
    static const char*      TEXTURE_TUNNEL =        "./data/tunnel2.tga";
    static const char*      TEXTURE_COLORMAP =      "./data/planet/colormap1.tga";
    static const char*      TEXTURE_CLOUDS =        "./data/planet/clouds1.tga";

    // 01-02-2004 - FIXE : Must be improved
    static gl::CStateManu<3>* g_pStatePlanet = 0;
};

CTunnel7::CTunnel7 ()
{

}

CTunnel7::~CTunnel7 ()
{
    file::CManager* pManager = file::CManager::Instance ();

    pManager->DeleteTexture2D (m_pTextureTunnel);
    pManager->DeleteTexture2D (m_pTexturePlanet);
    pManager->DeleteTexture2D (m_pTextureClouds);

    delete m_pSphere1;
    delete m_pSphere2;

    delete m_pFade1;
    delete m_pFade2;

    delete g_pStatePlanet;
    g_pStatePlanet = 0;
}

bool CTunnel7::Load ()
{
    file::CManager* pManager = file::CManager::Instance ();

    m_pTextureTunnel = pManager->CreateTexture2D (TEXTURE_TUNNEL);
    m_pTexturePlanet = pManager->CreateTexture2D (TEXTURE_COLORMAP);
    m_pTextureClouds = pManager->CreateTexture2D (TEXTURE_CLOUDS);

    m_pSphere1 = new gl::CObjectDL;
    m_pSphere1->TextureActive (gl::TEXTURE0 | gl::TEXTURE1 | gl::TEXTURE2);
    m_pSphere1->Sphere (1.0f, 24, 24);

    m_pSphere2 = new gl::CObjectDL;
    m_pSphere2->TextureActive (gl::TEXTURE0 | gl::TEXTURE1 | gl::TEXTURE2);
    m_pSphere2->Sphere (1.1f, 24, 24);

    m_pFade1 = new gl::CFade;
    m_pFade1->Times (0.0f, 0.5f);
    m_pFade1->Fade (gl::FADE_OUT);
    m_pFade1->Color (gtl::CColor3<float> (0.0f, 0.0f, 0.0f));
    m_pFade1->Init ();

    m_pFade2 = new gl::CFade;
    m_pFade2->Times (9.75f, 10.0f);
    m_pFade2->Fade (gl::FADE_IN);
    m_pFade2->Color (gtl::CColor3<float> (0.0f, 0.0f, 0.0f));
    m_pFade2->Init ();

    g_pStatePlanet = new gl::CStateManu<3>;
    g_pStatePlanet->Init (0, GL_DEPTH_TEST);
    g_pStatePlanet->Init (1, GL_LIGHTING);
    g_pStatePlanet->Init (2, GL_TEXTURE_2D);

    return true;
}

void CTunnel7::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    glShadeModel (GL_SMOOTH);
    glClearColor (0.0f, 0.0f, 0.1f, 0.0f);

    glLightfv (GL_LIGHT0, GL_AMBIENT, gtl::CVector4<float> (0.3f, 0.3f, 0.3f, 0.3f));
    glLightfv (GL_LIGHT0, GL_DIFFUSE, gtl::CVector4<float> (0.9f, 0.9f, 0.9f, 0.9f));
    glLightfv (GL_LIGHT0, GL_SPECULAR, gtl::CVector4<float> (1.0f, 1.0f, 1.0f, 1.0f));

    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->SetViewDistance (512.f);
    pCamera->Init (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (0, 1, 0));
    pCamera->Move (-2.0f);

	glEnable (GL_LIGHT0);
}

void CTunnel7::End ()
{
    gl::CCamera::Kill ();

    glDisable (GL_LIGHT0);
}

bool CTunnel7::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTunnel7::Update ()
{
    particle::CManager::Instance ()->Update ();
}

void CTunnel7::Render () const
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

    gl::CCamera::Instance ()->LookAt ();

    glPushMatrix ();
        float fDisplacement = MAX (240 - (48 * fTime), 0);
        glTranslatef (0, fDisplacement, 0);
        float Position[] = {-1.0f, -1.0f, 0.0f, 0.0f};
        glLightfv (GL_LIGHT0, GL_POSITION, Position);
        glPushMatrix ();
            glRotatef (45.f, 1, 0, 0);
            glRotatef (15.f, 0, 1, 0);
            glRotatef (60.f, 0, 0, 1);
            glRotatef (fTime * 36 + 180, 0, 0, 1);
            _RenderPlanet (fTime);
        glPopMatrix ();
    glPopMatrix ();

    glEnable (GL_DEPTH_TEST);
    glDepthMask (GL_FALSE);
        particle::CManager::Instance ()->Render ();
    glDepthMask (GL_TRUE);
    glDisable (GL_DEPTH_TEST);

    _RenderTunnel (fTime);

    m_pFade2->Render (fTime);
}

EType CTunnel7::Type ()
{
    return TYPE_TUNNEL1;
}

bool CTunnel7::HUD ()
{
    return true;
}

void CTunnel7::_RenderPlanet (float fTime) const
{
    g_pStatePlanet->Enable ();
        {
            gl::CStateAuto<GL_CULL_FACE> Enable;
            glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
            m_pTexturePlanet->Bind ();
            m_pSphere1->Render ();
        }
        {
            gl::CStateAuto<GL_BLEND> Enable;
		    glDepthMask (GL_FALSE);
                glBlendFunc (GL_SRC_ALPHA, GL_ONE);
                glColor4f (1.0f, 1.0f, 1.0f, 0.25f);
                m_pTextureClouds->Bind ();
                m_pSphere2->Render ();
		    glDepthMask (GL_TRUE);
        }
    g_pStatePlanet->Disable ();
}

void CTunnel7::_RenderTunnel (float fTime) const
{
    gl::CStateAuto<GL_BLEND> Enable;
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glActiveTextureARB (GL_TEXTURE0_ARB);
	glEnable (GL_TEXTURE_2D);
	m_pTextureTunnel->Bind ();

    glPushMatrix ();
    glTranslatef (0, -3, 0);
    for (float i = 0; i < CIRCLES; i += 1.0f)
    {
        glBegin (GL_QUADS);
            float fIncCercle = 360.0f / SEGMENTS;
            for (float p = 0.0f; p < 360.0f; p += fIncCercle * 1)
            {    
                float x1 = sinf ((float)PI / 180.0f * p);
                float y1 = cosf ((float)PI / 180.0f * p);
                float x2 = x1;
                float y2 = y1;
                float x3 = sinf ((float)PI / 180.0f * (p + fIncCercle));
                float y3 = cosf ((float)PI / 180.0f * (p + fIncCercle));
                float x4 = x3;
                float y4 = y3;
                
                float u1 = (p * TEXTURE_WRAPPING) / 360.0f;
                float u2 = ((p + fIncCercle) * TEXTURE_WRAPPING) / 360.0f;
                float v1 = (((float) i + 0) * TEXTURE_WRAPPING) / (float) CIRCLES;
                float v2 = (((float) i + 1) * TEXTURE_WRAPPING) / (float) CIRCLES;

                u1 += fTime * 0.2f;
                u2 += fTime * 0.2f;
                v1 += fTime * 2.0f;
                v2 += fTime * 2.0f;

                float fColor1 = ((1 - (i + 0) / CIRCLES) / 2.0f);
                float fColor2 = ((1 - (i + 1) / CIRCLES) / 2.0f);
                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u1 * TEXTURE_DETAIL_X, v1 * TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor1); 
                glVertex3f (x1, 0.0f, y1);

                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u1 * TEXTURE_DETAIL_X, v2 * TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor2); 
                glVertex3f (x2, DISPLACEMENT, y2);

                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u2 * TEXTURE_DETAIL_X, v2 * TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor2); 
                glVertex3f (x4, DISPLACEMENT, y4);

                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u2 * TEXTURE_DETAIL_X, v1 * TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor1); 
                glVertex3f (x3, 0.0f, y3);
            }
        glEnd ();
        glTranslatef (0, DISPLACEMENT, 0);
    }
    glPopMatrix ();

	glActiveTextureARB (GL_TEXTURE0_ARB);
	glDisable (GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, 0);
}
