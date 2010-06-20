//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-29-2004
//! \file ./scene/element_tunnel5.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_tunnel5.h"
#include "../particle/index.h"

using namespace scene;

namespace scene 
{
    static const float      TIME =                  2.5f;
    static const float      DISPLACEMENT =          1.0f;
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

CTunnel5::CTunnel5 ()
{

}

CTunnel5::~CTunnel5 ()
{
    file::CManager* pManager = file::CManager::Instance ();
    pManager->DeleteTexture2D (m_pTextureTunnel);
    pManager->DeleteTexture2D (m_pTexturePlanet);
    pManager->DeleteTexture2D (m_pTextureClouds);
}

bool CTunnel5::Load ()
{
    file::CManager* pManager = file::CManager::Instance ();
    m_pTextureTunnel = pManager->CreateTexture2D (TEXTURE_TUNNEL);
    m_pTexturePlanet = pManager->CreateTexture2D (TEXTURE_COLORMAP);
    m_pTextureClouds = pManager->CreateTexture2D (TEXTURE_CLOUDS);

    return true;
}

void CTunnel5::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    glShadeModel (GL_SMOOTH);
    glClearColor (0.0f, 0.0f, 0.1f, 0.0f);

    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->SetViewDistance (512.f);
    pCamera->Init (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (0, 1, 0));
    pCamera->Move (-2.0f);
/*
	unsigned char *pTexture = new unsigned char [WINDOW_WIDTH * WINDOW_HEIGHT * 3];
	memset (pTexture, 0, WINDOW_WIDTH * WINDOW_HEIGHT * 3 * sizeof(unsigned char));	
	glGenTextures (1, &m_uiTextureMotionBlur);								
	glBindTexture (GL_TEXTURE_RECTANGLE_ARB, m_uiTextureMotionBlur);					
	glTexImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, pTexture);						
	delete [] pTexture;
*/
}

void CTunnel5::End ()
{
    gl::CCamera::Kill ();
}

bool CTunnel5::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTunnel5::Update ()
{
    particle::CManager::Instance ()->Update ();
}

void CTunnel5::Render () const
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

    gl::CCamera::Instance ()->LookAt ();
/*
	// 29-12-2004 - Frist pass
	glPushMatrix ();
		glColor4f (1.0f, 1.0f, 1.0f, fTime / TIME);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE);	
        glEnable (GL_BLEND);
		glEnable (GL_TEXTURE_RECTANGLE_ARB);

		glMatrixMode (GL_PROJECTION);			
		glPushMatrix ();
			glLoadIdentity ();
			glOrtho (0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1);
			glMatrixMode (GL_MODELVIEW);
			glLoadIdentity ();

			glBindTexture (GL_TEXTURE_RECTANGLE_ARB, m_uiTextureMotionBlur);
			glBegin (GL_QUADS);
				glTexCoord2f (0.0f, WINDOW_HEIGHT); glVertex2f (0, 0);
				glTexCoord2f (0.0f, 0.0f); glVertex2f (0, WINDOW_HEIGHT);
				glTexCoord2f (WINDOW_WIDTH, 0.0f); glVertex2f (WINDOW_WIDTH, WINDOW_HEIGHT);
				glTexCoord2f (WINDOW_WIDTH, WINDOW_HEIGHT); glVertex2f (WINDOW_WIDTH, 0);
			glEnd ();
		
			glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glMatrixMode (GL_MODELVIEW);

		glDisable (GL_BLEND);
		glDisable (GL_TEXTURE_RECTANGLE_ARB);
	glPopMatrix ();
*/
    // 29-12-2004 - Second pass
    glEnable (GL_DEPTH_TEST);
    glDepthMask (GL_FALSE);
        particle::CManager::Instance ()->Render ();
    glDepthMask (GL_TRUE);
    glDisable (GL_DEPTH_TEST);

    _RenderTunnel (fTime);
/*
	glEnable (GL_TEXTURE_RECTANGLE_ARB);
		glBindTexture (GL_TEXTURE_RECTANGLE_ARB, m_uiTextureMotionBlur);
		glCopyTexImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	glDisable (GL_TEXTURE_RECTANGLE_ARB);
*/
}

EType CTunnel5::Type ()
{
    return TYPE_TUNNEL5;
}

bool CTunnel5::HUD ()
{
    return true;
}

void CTunnel5::_RenderTunnel (float fTime) const
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
            float fTunnelDeplacement = (fTime + 2.5f) * TEXTURE_SPEED;
            float fDisplacementX = sinf ((float)PI / 180.0f * (fTunnelDeplacement * MOVE_SPEED1) + i * 0.2f) * 0.2f;
            float fDisplacementY = cosf ((float)PI / 180.0f * (fTunnelDeplacement * MOVE_SPEED1) + i * 0.2f) * 0.1f;
            fDisplacementX -= cosf ((float)PI / 180.0f * (fTunnelDeplacement * MOVE_SPEED2) + i * 0.2f) * 0.2f;
            fDisplacementY -= sinf ((float)PI / 180.0f * (fTunnelDeplacement * MOVE_SPEED2) + i * 0.2f) * 0.1f;

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

                    u1 += fTime * 0.2f;
                    u2 += fTime * 0.2f;
                    v1 += fTime * 2.0f;
                    v2 += fTime * 2.0f;

                    float fColor1 = ((1 - (i + 0) / CIRCLES) / 2.0f);
                    float fColor2 = ((1 - (i + 1) / CIRCLES) / 2.0f);
                    glTexCoord2f (u1 * TEXTURE_DETAIL_X, v1 * TEXTURE_DETAIL_Y);
                    glColor4f (1.0f, 1.0f, 1.0f, fColor1); 
                    glVertex3f (x1, 0.0f, y1);

                    glTexCoord2f (u1*TEXTURE_DETAIL_X, v2*TEXTURE_DETAIL_Y);
                    glColor4f (1.0f, 1.0f, 1.0f, fColor2); 
                    glVertex3f (x2, DISPLACEMENT, y2);

                    glTexCoord2f (u2*TEXTURE_DETAIL_X, v2*TEXTURE_DETAIL_Y);
                    glColor4f (1.0f, 1.0f, 1.0f, fColor2); 
                    glVertex3f (x4, DISPLACEMENT, y4);

                    glTexCoord2f (u2*TEXTURE_DETAIL_X, v1*TEXTURE_DETAIL_Y);
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
