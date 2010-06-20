//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_font.cpp
//! \brief Classe CFont, pour l'affichage de caractères.
//////////////////////////////////////////////////////////////////////////////

#include "../include/gtl_font.h"
#include "../include/gtl_gl.h"

namespace gtl {

CFont::CFont ()
{
    m_bLoaded = false;
    m_uiDisplayListIndex = 0;
    m_fColor[0] = m_fColor[1] = m_fColor[2] = 1.0f;
    m_fScale[0] = m_fScale[1] = m_fScale[2] = 1.0f;
    m_fSpace = 0.0f;
    m_uiOption = 0;
}

CFont::~CFont ()
{
    if (m_bLoaded)
	    glDeleteLists (m_uiDisplayListIndex, 256);
}

void CFont::Begin () const
{
	glPushAttrib (GL_ALL_ATTRIB_BITS);
	    glBindTexture (GL_TEXTURE_2D, m_uiFontIndex);
	    glEnable (GL_TEXTURE_2D);

	    glColor3fv (m_fColor);
	    if (m_uiOption & FONT_BLEND)
	    {
	         glBlendFunc (GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	         glEnable (GL_BLEND);
	    }
  
	    //if (m_uiOption & FONT_SPACING)
	    //     Build ();
}

void CFont::End () const
{
	glPopAttrib ();   
}

void CFont::Enable (unsigned int uiOption)
{
    m_uiOption |= uiOption;
}

void CFont::Disable (unsigned int uiOption)
{
    m_uiOption &= ~uiOption;
}

void CFont::Size (float x, float y, float z)
{
    m_fScale [0] = x / m_fSize[0];
    m_fScale [1] = y / m_fSize[1];
    m_fScale [2] = z;
}

void CFont::Color (float x, float y, float z)
{
    m_fColor [0] = x;
    m_fColor [1] = y;
    m_fColor [2] = z;
}

void CFont::Spacing (float fSpace)
{
    m_fSpace = fSpace;
}

}; //namespace gtl

