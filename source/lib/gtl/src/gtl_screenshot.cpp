//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_screenshot.cpp
//! \brief Classe CScreenshot, pour la capture d'écran.
//////////////////////////////////////////////////////////////////////////////

#include "../include/gtl_screenshot.h"
#include "../include/gtl_image_tga.h"
#include "../include/gtl_gl.h"
#include <stdio.h>

namespace gtl {

CScreenshot::CScreenshot (const char* szFilename)
{
	m_iOriginX = 0;
	m_iOriginY = 0;
	m_iWidth = 0;
	m_iHeight = 0;
	m_bIsConfigurated = false;
	if (szFilename) m_szFilename = szFilename;
}

CScreenshot::CScreenshot (int iOriginX, int iOriginY, int iWidth, int iHeight, const char* szFilename)
{
	m_iOriginX = iOriginX;
	m_iOriginY = iOriginY;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_bIsConfigurated = m_iWidth > 0 && m_iHeight > 0 ? true : false;
	if (szFilename) m_szFilename = szFilename;
}

void CScreenshot::Config (int iOriginX, int iOriginY, int iWidth, int iHeight)
{
	m_iOriginX = iOriginX;
	m_iOriginY = iOriginY;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_bIsConfigurated = m_iWidth > 0 && m_iHeight > 0 ? true : false;
}

bool CScreenshot::Snap (const char* szFilename)
{
	if (!m_bIsConfigurated)
		return false;

	char szFilenameBuffer [64];
	memset (szFilenameBuffer, '\0', 64);

	if (!szFilename)
	{
		memcpy (szFilenameBuffer, m_szFilename.c_str (), m_szFilename.size ());
		sprintf (szFilenameBuffer + m_szFilename.size (), "%04d.tga", m_iIndex);
	}
	else
	{
		m_szFilename = szFilename;
		memcpy (szFilenameBuffer, m_szFilename.c_str (), m_szFilename.size ());
		sprintf (szFilenameBuffer + m_szFilename.size (), ".tga");
	}

	if (m_szFilename.empty ())
		return false;

	unsigned char *pucData = new unsigned char [m_iWidth * m_iHeight * 3];
	glReadPixels (m_iOriginX, m_iOriginY, m_iWidth, m_iHeight, GL_RGB, GL_UNSIGNED_BYTE, pucData);

	CImageTGA Image;
	Image.New (m_iWidth - m_iOriginX, m_iHeight - m_iOriginY, 24, pucData);
	Image.SaveAs (szFilenameBuffer);

	m_iIndex++;

	delete [] pucData;

	return true;
}

}; // namespace gtl
