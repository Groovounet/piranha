//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-18-2004
//! \file ./gl/fade.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./fade.h"
#include "./state_auto.h"
#include "../window/window.h"

using namespace gl;

CFade::CFade ()
{
    m_Division = gtl::CVector2<float> (1, 1);
    m_fStart = 0;
    m_fEnd = 1;
    m_Type = FADE_IN;
    m_pObject = new CObjectDL;
}

CFade::~CFade ()
{
    delete m_pObject;
}

void CFade::Init ()
{
    m_pObject->Plane (gtl::CVector3<float> (320.f, 240.f, 0.f), gtl::CVector2<float>(640.f, 480.f), m_Division);
}

void CFade::Render (float fTime) const
{
    glPushMatrix ();
        glMatrixMode (GL_PROJECTION);
	    glPushMatrix ();
            glViewport (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
            glMatrixMode (GL_PROJECTION);
		    glLoadIdentity ();
		    glOrtho (0, 640, 0, 480, -1, 1);
		    glMatrixMode (GL_MODELVIEW);
		    glLoadIdentity ();

            _RenderLayer (fTime);

		    glMatrixMode (GL_PROJECTION);
	    glPopMatrix ();
	    glMatrixMode (GL_MODELVIEW);
    glPopMatrix ();
}

void CFade::Times (float fStart, float fEnd)
{
    m_fStart = fStart;
    m_fEnd = fEnd;
}

void CFade::Fade (const EFade & Fade)
{
    m_Type = Fade;
}

void CFade::Division (float x, float y)
{
    m_Division = gtl::CVector2<float> (x, y);
}

void CFade::Color (const gtl::CColor3<float> & Color)
{
    m_Color (gtl::R) = Color (gtl::R);
    m_Color (gtl::G) = Color (gtl::G);
    m_Color (gtl::B) = Color (gtl::B);
}

void CFade::TextureActive (unsigned int uiTexture)
{
    m_pObject->TextureActive (uiTexture);
}

void CFade::_RenderLayer (float fTime) const
{
    CStateAuto<GL_BLEND> Blend;
    //CStateAuto<GL_TEXTURE_RECTANGLE_ARB> Texture;

	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gtl::CColor4<float> Color = m_Color;
    if (m_Type == FADE_IN)
		Color (gtl::A) = fTime > m_fStart ? (fTime - m_fStart) / (m_fEnd - m_fStart) : 0.0f;
    else //if (m_Type == FADE_OUT)
        Color (gtl::A) = fTime > m_fStart ? 1.f - (fTime - m_fStart) / (m_fEnd - m_fStart) : 1.0f;
    glColor4fv (Color);
    //m_pTextureBorder->Bind ();
    m_pObject->Render ();
}
