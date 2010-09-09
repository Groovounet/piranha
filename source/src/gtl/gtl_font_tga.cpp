//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_font_tga.cpp
//! \brief Classe CFontTGA, pour l'affichage de caractères à partir d'une image TGA.
//////////////////////////////////////////////////////////////////////////////

#include "gtl_font_tga.h"
#include "gtl_image_tga.h"
#include "gtl_gl.h"

#include <cstdio>

namespace gtl {

CFontTGA::CFontTGA (const char* szFilename)
{
    if (szFilename != 0)
        Load (szFilename);
}

CFontTGA::~CFontTGA ()
{

}

void CFontTGA::Print (int x, int y, const char *szMsg, ...) const
{
	char szText[FONT_BUFFER];
	va_list ap;

	if (szMsg == 0)
		return;

	va_start (ap, szMsg);
	    vsprintf (szText, szMsg, ap);
	va_end (ap);

	glLoadIdentity ();
	glTranslated (x, y, 0);
	glListBase (m_uiDisplayListIndex);

	if (m_uiOption & FONT_SCALE)
		glScalef (m_fScale[0], m_fScale[1], m_fScale[2]);

	glCallLists (strlen (szText), GL_UNSIGNED_BYTE, szText);
}

void CFontTGA::Build ()
{
    if (m_uiDisplayListIndex)
        glDeleteLists (m_uiDisplayListIndex, 256);
        
	m_uiDisplayListIndex = glGenLists (256);
	glBindTexture (GL_TEXTURE_2D, m_uiFontIndex);
	for (int i = 0; i < 256; i++)
	{
		float fTexCoordX = float (i%16) / 16.0f;
		float fTexCoordY = float (i/16) / 16.0f;

		glNewList (m_uiDisplayListIndex + i, GL_COMPILE);
			glBegin (GL_QUADS);
				glTexCoord2f (fTexCoordX, 1.0f - fTexCoordY - 0.0625f);
				glVertex2f (0, 0);
				
				glTexCoord2f (fTexCoordX + 0.0625f, 1.0f - fTexCoordY - 0.0625f);
				glVertex2f (m_fSize[0], 0);
				
				glTexCoord2f (fTexCoordX + 0.0625f, 1.0f - fTexCoordY);
				glVertex2f (m_fSize[0], m_fSize[1]);
				
				glTexCoord2f (fTexCoordX, 1.0f - fTexCoordY);
				glVertex2f (0, m_fSize[1]);
			glEnd ();
			if (m_uiOption & FONT_SPACING)
				glTranslated (m_fSpace, 0, 0);
			else
				glTranslated (m_fSize[0] * 1.0f/*0.75f*/, 0, 0);
		glEndList ();
	}
}

bool CFontTGA::Load (const char* szFilename)
{
	CImageTGA Font (szFilename);
	if (!Font.IsLoaded ())
		return false;
    
	glGenTextures (1, &m_uiFontIndex);
	glBindTexture (GL_TEXTURE_2D, m_uiFontIndex);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, Font.Width (), Font.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Font.Data ());

	m_fSize[0] = Font.Width () / 16.0f;
	m_fSize[1] = Font.Height () / 16.0f;

	Build ();
	
	return (m_bLoaded = true);
}

}; // namespace gtl

