//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./scene/element_terrain1.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_terrain1.h"
#include "../gl/index.h"

using namespace scene;

static const float      TIME =                  5.f;
static const float      DISPLACEMENT =          1.f;
static const float      SEGMENTS =              24.f;
static const float      CIRCLES =               160.f;
static const float      TEXTURE_SPEED =         2.4f;
static const float      TEXTURE_DETAIL_X =      1.0f;
static const float      TEXTURE_DETAIL_Y =      4.0f;
static const float      TEXTURE_WRAPPING =      2.0f;
static const char*      TEXTURE_TUNNEL =        "./data/tunnel2.tga";
static const float      RADIUS =                8.f;

CTerrain1::CTerrain1 ()
{
    m_pTerrain = 0;
}

CTerrain1::~CTerrain1 ()
{
    terrain::CTerrain::Delete (m_pTerrain);
    file::CManager::Instance ()->DeleteTexture2D (m_pTunnelTex);
}

bool CTerrain1::Load ()
{
    m_pTerrain = terrain::CTerrain::Create ();
    m_pTunnelTex = file::CManager::Instance ()->CreateTexture2D (TEXTURE_TUNNEL);

    if (gl::ARB_texture_rectangle)
    {
        m_iTextureType = GL_TEXTURE_RECTANGLE_ARB;
    }
    else if (gl::NV_texture_rectangle)
    {
        m_iTextureType = GL_TEXTURE_RECTANGLE_NV;
    }

    return true;
}

void CTerrain1::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    glPushAttrib (GL_ALL_ATTRIB_BITS);

    glShadeModel (GL_SMOOTH);
    glClearColor (0.0f, 0.0f, 0.1f, 0.0f);

    glLightfv (GL_LIGHT0, GL_AMBIENT, gtl::CColor4<float>(0.3f, 0.3f, 0.3f, 0.3f));
	glLightfv (GL_LIGHT0, GL_DIFFUSE, gtl::CColor4<float>(0.9f, 0.9f, 0.9f, 0.9f));
	glLightfv (GL_LIGHT0, GL_SPECULAR, gtl::CColor4<float>(1.0f, 1.0f, 1.0f, 1.0f));

    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->Enable (gl::CAMERA_FRUSTUM);
    pCamera->SetViewDistance (512.f);
    pCamera->Init (gtl::CVector3<float> (0, 96, 0), gtl::CVector3<float> (0, 106, 0));
    pCamera->MoveUp (80.f);
    pCamera->LookAt (1200.f, 0);

	glGenTextures (1, &m_uiTextureMotionBlur);								
	glBindTexture (m_iTextureType, m_uiTextureMotionBlur);					
	glTexImage2D (m_iTextureType, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);						

	glEnable (GL_LIGHT0);
}

void CTerrain1::End ()
{
    glDeleteTextures (1, &m_uiTextureMotionBlur);
	glDisable (GL_LIGHT0);
    glPopAttrib ();
}

bool CTerrain1::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTerrain1::Update ()
{
    m_pTerrain->Update ();
}

void CTerrain1::Render () const
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

	glClear (GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
    glTranslatef (0, MIN (- (64 - 64 * fTime / (TIME - 1)), 0), 0);
    gl::CCamera::Instance ()->LookAt ();

    glLightfv (GL_LIGHT0, GL_POSITION, gtl::CVector4<float> (256.0f, 256.0f, 128.0f, 1.0f));

    // 29-12-2004 - Frist pass
    glEnable (GL_DEPTH_TEST);
        glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
        m_pTerrain->Render ();
        _RenderTunnel (fTime);
    glDisable (GL_DEPTH_TEST);

	// 29-12-2004 - Second pass
	glPushMatrix ();
		glColor4f (1.0f, 1.0f, 1.0f, 0.95f);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
        glEnable (GL_BLEND);
		glEnable (m_iTextureType);

		glMatrixMode (GL_PROJECTION);			
		glPushMatrix ();
			glLoadIdentity ();
			glOrtho (0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1);
			glMatrixMode (GL_MODELVIEW);
			glLoadIdentity ();

			glBindTexture (m_iTextureType, m_uiTextureMotionBlur);
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
		glDisable (m_iTextureType);
	glPopMatrix ();

    // 29-12-2004 - Save the new motion texture.
	glEnable (m_iTextureType);
		glBindTexture (m_iTextureType, m_uiTextureMotionBlur);
		glCopyTexImage2D (m_iTextureType, 0, GL_RGB, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	glDisable (m_iTextureType);
}

EType CTerrain1::Type ()
{
    return TYPE_TERRAIN1;
}

bool CTerrain1::HUD ()
{
    return true;
}

void CTerrain1::_RenderTunnel (float fTime) const
{
	glActiveTextureARB (GL_TEXTURE0_ARB);
	glEnable (GL_TEXTURE_2D);
	m_pTunnelTex->Bind ();

    gl::CStateAuto<GL_BLEND> Blend;
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix ();
        gtl::CVector3<float> Position = gl::CCamera::Instance ()->GetPosition ();
        glTranslatef (Position (gtl::X), Position (gtl::Y), Position (gtl::Z) - DISPLACEMENT * CIRCLES / 2);
        glRotatef (90.f, 1.0f, 0.0f, 0.0f);

        glColor4fv (gtl::CColor4<float>(1.0f, 1.0f, 1.0f, 1.0f - 1.0f * (fTime / TIME)));
        glBegin (GL_QUADS);
            float fInc = 360.0f / SEGMENTS;
            for (float p = 0.0f; p < 360.0f; p += fInc * 1)
            {    
                float x1 = sinf (p * (float)PI / 180.0f) * RADIUS;
                float y1 = cosf (p * (float)PI / 180.0f) * RADIUS;
                float x2 = sinf ((p + fInc) * (float)PI / 180.0f) * RADIUS;
                float y2 = cosf ((p + fInc) * (float)PI / 180.0f) * RADIUS;
                
                float u1 = (p * TEXTURE_WRAPPING) / 360.0f;
                float u2 = ((p + fInc) * TEXTURE_WRAPPING) / 360.0f;
                float v1 = 0;
                float v2 = (CIRCLES * TEXTURE_WRAPPING) / (float) CIRCLES;

                v1 += fTime * 0.5f;
                v2 += fTime * 0.5f;

                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u1 * TEXTURE_DETAIL_X, v1 * TEXTURE_DETAIL_Y);
                glVertex3f (x1, 0.0f, y1);

                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u1 * TEXTURE_DETAIL_X, v2 * TEXTURE_DETAIL_Y);
                glVertex3f (x1, DISPLACEMENT * CIRCLES, y1);

                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u2 * TEXTURE_DETAIL_X, v2 * TEXTURE_DETAIL_Y);
                glVertex3f (x2, DISPLACEMENT * CIRCLES, y2);

                glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u2 * TEXTURE_DETAIL_X, v1 * TEXTURE_DETAIL_Y);
                glVertex3f (x2, 0.0f, y2);
            }
        glEnd ();
    glPopMatrix ();

	glActiveTextureARB (GL_TEXTURE0_ARB);
	glDisable (GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, 0);
}
