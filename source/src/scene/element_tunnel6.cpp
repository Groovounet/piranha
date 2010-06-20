//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-26-2004
//! \file ./scene/element_tunnel6.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_tunnel6.h"
#include "../particle/index.h"

using namespace scene;

namespace scene 
{
    static const float      TIME =                  2.5f;
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
};

CTunnel6::CTunnel6 ()
{

}

CTunnel6::~CTunnel6 ()
{
    file::CManager* pManager = file::CManager::Instance ();
    pManager->DeleteTexture2D (m_pTextureTunnel);
    pManager->DeleteTexture2D (m_pTexturePlanet);
    pManager->DeleteTexture2D (m_pTextureClouds);
}

bool CTunnel6::Load ()
{
    file::CManager* pManager = file::CManager::Instance ();
    m_pTextureTunnel = pManager->CreateTexture2D (TEXTURE_TUNNEL);
    m_pTexturePlanet = pManager->CreateTexture2D (TEXTURE_COLORMAP);
    m_pTextureClouds = pManager->CreateTexture2D (TEXTURE_CLOUDS);

    return true;
}

void CTunnel6::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    glShadeModel (GL_SMOOTH);
    glClearColor (0.0f, 0.0f, 0.1f, 0.0f);

    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->SetViewDistance (512.f);
    pCamera->Init (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (0, 1, 0));
    pCamera->Move (-2.0f);
}

void CTunnel6::End ()
{
    gl::CCamera::Kill ();
}

bool CTunnel6::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTunnel6::Update ()
{
    particle::CManager::Instance ()->Update ();
}

void CTunnel6::Render () const
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
}

EType CTunnel6::Type ()
{
    return TYPE_TUNNEL1;
}

bool CTunnel6::HUD ()
{
    return true;
}

void CTunnel6::_RenderTunnel (float fTime) const
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
            float fTunnelDeplacement = (fTime + 5.0f) * TEXTURE_SPEED;
            float fDisplacementX = sinf ((float)PI / 180.0f * (fTunnelDeplacement * MOVE_SPEED1) + i * 0.2f) * 0.2f * (1.0f - fTime / TIME);
            float fDisplacementY = cosf ((float)PI / 180.0f * (fTunnelDeplacement * MOVE_SPEED1) + i * 0.2f) * 0.1f * (1.0f - fTime / TIME);
            fDisplacementX -= cosf ((float)PI / 180.0f * (fTunnelDeplacement * MOVE_SPEED2) + i * 0.2f) * 0.2f * (1.0f - fTime / TIME);
            fDisplacementY -= sinf ((float)PI / 180.0f * (fTunnelDeplacement * MOVE_SPEED2) + i * 0.2f) * 0.1f * (1.0f - fTime / TIME);

            glBegin (GL_QUADS);
                float fIncCercle = 360.0f / SEGMENTS;
                for (float p = 0.0f; p < 360.0f; p += fIncCercle * 1)
                {    
                    float x1 = sinf ((float)PI / 180.0f * p);
                    float y1 = cosf ((float)PI / 180.0f * p);
                    float x2 = x1 + fDisplacementX;
                    float y2 = y1 + fDisplacementY;
                    float x3 = sinf ((float)PI / 180.0f * (p + fIncCercle));
                    float y3 = cosf ((float)PI / 180.0f * (p + fIncCercle));
                    float x4 = x3 + fDisplacementX;
                    float y4 = y3 + fDisplacementY;
                    
                    float u1 = (p * TEXTURE_WRAPPING) / 360.0f;
                    float u2 = ((p + fIncCercle) * TEXTURE_WRAPPING) / 360.0f;
                    float v1 = (((float) i + 0) * TEXTURE_WRAPPING) / (float) CIRCLES;
                    float v2 = (((float) i + 1) * TEXTURE_WRAPPING) / (float) CIRCLES;

                    v1 += fTime * 2.0f;
                    v2 += fTime * 2.0f;

                    float fColor1 = ((1 - (i + 0) / CIRCLES) / 2.0f);
                    float fColor2 = ((1 - (i + 1) / CIRCLES) / 2.0f);

                    glTexCoord2f (u1 * TEXTURE_DETAIL_X, v1 * TEXTURE_DETAIL_Y);
                    glColor4f (1.0f, 1.0f, 1.0f, fColor1); 
                    glVertex3f (x1, 0.0f, y1);

                    glTexCoord2f (u1 * TEXTURE_DETAIL_X, v2 * TEXTURE_DETAIL_Y);
                    glColor4f (1.0f, 1.0f, 1.0f, fColor2); 
                    glVertex3f (x2, DISPLACEMENT, y2);

                    glTexCoord2f (u2 * TEXTURE_DETAIL_X, v2 * TEXTURE_DETAIL_Y);
                    glColor4f (1.0f, 1.0f, 1.0f, fColor2); 
                    glVertex3f (x4, DISPLACEMENT, y4);

                    glTexCoord2f (u2 * TEXTURE_DETAIL_X, v1 * TEXTURE_DETAIL_Y);
                    glColor4f (1.0f, 1.0f, 1.0f, fColor1); 
                    glVertex3f (x3, 0.0f, y3);
                }
            glEnd ();
            glTranslatef (fDisplacementX, DISPLACEMENT, fDisplacementY);
        }
    glPopMatrix ();

	glActiveTextureARB (GL_TEXTURE0_ARB);
	glDisable (GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, 0);
}
