//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./scene/element_terrain5.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_terrain5.h"
#include "../gl/index.h"
#include "../util/index.h"
#include "../particle/index.h"

using namespace scene;

static const float      TIME =                  10.f;

CTerrain5::CTerrain5 ()
{
    m_pTerrain = 0;
}

CTerrain5::~CTerrain5 ()
{
    terrain::CTerrain::Delete (m_pTerrain);
}

bool CTerrain5::Load ()
{
    m_pTerrain = terrain::CTerrain::Create ();

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

void CTerrain5::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    glPushAttrib (GL_ALL_ATTRIB_BITS);

    glShadeModel (GL_SMOOTH);
    glClearColor (0.0f, 0.0f, 0.1f, 0.0f);

	glGenTextures (1, &m_uiTextureMotionBlur);								
	glBindTexture (m_iTextureType, m_uiTextureMotionBlur);					
	glTexImage2D (m_iTextureType, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);						
}

void CTerrain5::End ()
{
    glDeleteTextures (1, &m_uiTextureMotionBlur);

    glPopAttrib ();
}

bool CTerrain5::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTerrain5::Update ()
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

    particle::CManager::Instance ()->Update ();
    m_pTerrain->Update ();

    if (fTime > TIME - 2)
    {
        m_Quake = gtl::CVector2<float>(0, 0);
        return;
    }

    if (fTime - m_fTimeQuake > 0.02f)
        m_Quake = gtl::CVector2<float>(gtl::CRand::Float (-4, 4), gtl::CRand::Float (-4, 4));
}

void CTerrain5::Render () const
{
	glClear (GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
    
    gl::CCamera::Instance ()->LookAt ();

    glTranslatef (m_Quake (gtl::X), m_Quake (gtl::Y), 0);
    // 29-12-2004 - Frist pass
    //glLightfv (GL_LIGHT0, GL_POSITION, gtl::CVector4<float> (256.0f, 256.0f, 128.0f, 1.0f));
    glEnable (GL_DEPTH_TEST);
        glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
        m_pTerrain->Render ();

        glDepthMask (GL_FALSE);
            particle::CManager::Instance ()->Render ();
        glDepthMask (GL_TRUE);
    glDisable (GL_DEPTH_TEST);

	// 29-12-2004 - Second pass
	glPushMatrix ();
		glColor4f (1.0f, 1.0f, 1.0f, 0.9f);
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

EType CTerrain5::Type ()
{
    return TYPE_TERRAIN5;
}

bool CTerrain5::HUD ()
{
    return true;
}
