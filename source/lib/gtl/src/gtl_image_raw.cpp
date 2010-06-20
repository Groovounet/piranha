//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_image_raw.cpp
//! \brief Classe CImageRAW, pour le chargement des images RAW.
//////////////////////////////////////////////////////////////////////////////

#include "../include/gtl_image_raw.h"
#include <fstream>

namespace gtl {

CImageRAW::CImageRAW ()
{
	m_bLoaded = false;
	m_bSaved = false;
	m_bChanged = false;
	m_pucData = 0;
}

CImageRAW::CImageRAW (const char* szFilename, unsigned short unSizeX, unsigned short unSizeY, unsigned char ucPixelSize)
{
	m_bLoaded = false;
	m_bSaved = false;
	m_bChanged = false;
	m_pucData = 0;

	m_unSizeX = unSizeX;
	m_unSizeY = unSizeY;
	m_ucTexelSize = ucPixelSize;
	
	if (szFilename != 0)
		Load (szFilename);
}

CImageRAW::~CImageRAW ()
{
	if (m_pucData != 0)
		delete m_pucData;
}

bool CImageRAW::New (unsigned short x, unsigned short y, unsigned char ucTexelSize, unsigned char* pucData)
{
	bool bSuccess = false;

	m_unSizeX = x;
	m_unSizeY = y;
	m_ucTexelSize = ucTexelSize;

	if (m_pucData)
		delete m_pucData;
	m_pucData = new unsigned char [x * y * ucTexelSize/8];
	if (m_pucData)
		bSuccess = true;

	if (pucData)
		memcpy (m_pucData, pucData, x * y * ucTexelSize/8);

	m_bLoaded = bSuccess;
	return bSuccess;
}

bool CImageRAW::Load (const char* szFilename)
{
	if (m_bLoaded)
	{
		if (m_pucData != 0)
		{
			delete m_pucData;
			m_pucData = 0;
		}
		m_bLoaded = false;
	}

	m_szFilename = szFilename;

	std::ifstream FileIn (m_szFilename.c_str (), std::ios::in | std::ios::binary);
	if (!FileIn)
		return false;

	unsigned int uiDataSize = m_unSizeX * m_unSizeY * m_ucTexelSize / 8;
	m_pucData = new unsigned char [uiDataSize];
	if (!m_pucData)
		return false;

	FileIn.read ((char*)m_pucData, uiDataSize);

	if (FileIn.fail () || FileIn.bad ())
	{
		delete m_pucData;
		return false;
	}
	else
		m_bLoaded = true;

	FileIn.close ();

	return m_bLoaded;
}

bool CImageRAW::Save ()
{
	if (m_bChanged)
		return SaveAs (m_szFilename.c_str ());
	else
		return true;
}

bool CImageRAW::SaveAs (const char* szFilename)
{
	if (!m_bLoaded && !m_bChanged)
		return false;

	std::ofstream FileOut (szFilename, std::ios::out | std::ios::binary);
	if (!FileOut)
		return false;

	unsigned int uiDataSize = m_unSizeX * m_unSizeY * m_ucTexelSize / 8;
	FileOut.write ((char*)m_pucData, uiDataSize);
	if (FileOut.fail () || FileOut.bad ())
	{
		delete m_pucData;
		return false;
	}
	else
		m_bSaved = true;

	FileOut.close ();

	m_bChanged = false;
	return m_bSaved;
}

unsigned char CImageRAW::GetValue (unsigned short x, unsigned short y, const EColor & Color) const
{
	unsigned char ucValue = 0;
	unsigned char ucTexelSize = m_ucTexelSize / 8;

	switch (Color)
	{
	default:
		break;
	case R:
		ucValue = m_pucData[((y * m_unSizeX) +x) * ucTexelSize + 2];
		break;
	case G:
		ucValue = m_pucData[((y * m_unSizeX) +x) * ucTexelSize + 1];
		break;
	case B:
		ucValue = m_pucData[((y * m_unSizeX) +x) * ucTexelSize + 0];
		break;
	case A:
		if ((m_ucTexelSize == 16) || (m_ucTexelSize == 32))
			ucValue = m_pucData[((y * m_unSizeX) +x) * ucTexelSize + 3];
		break;
	}

	return ucValue;
}

bool CImageRAW::SetValue (unsigned short x, unsigned short y, const EColor & Color, unsigned char ucValue) 
{
	bool bSuccess = false;
	unsigned char ucTexelSize = m_ucTexelSize / 8;

	switch (Color)
	{
	default:
		break;
	case R:
		m_pucData[((y * m_unSizeX) +x) * ucTexelSize + 2] = ucValue;
		bSuccess = true;
		break;
	case G:
		m_pucData[((y * m_unSizeX) +x) * ucTexelSize + 1] = ucValue;
		bSuccess = true;
		break;
	case B:
		m_pucData[((y * m_unSizeX) +x) * ucTexelSize + 0] = ucValue;
		bSuccess = true;
		break;
	case A:
		if ((m_ucTexelSize == 16) || (m_ucTexelSize == 32))
		{
			m_pucData[((y * m_unSizeX) +x) * ucTexelSize + 3] = ucValue;
			bSuccess = true;
		}
		break;
	}

	return bSuccess;
}

}; // namespace gtl
