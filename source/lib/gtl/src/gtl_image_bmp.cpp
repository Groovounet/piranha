//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_image_bmp.cpp
//! \brief Classe CImageBMP, pour le chargement des images BMP.
//////////////////////////////////////////////////////////////////////////////

#include "../include/gtl_image_bmp.h"
#include <fstream>

namespace gtl {

CImageBMP::CImageBMP (const char* szFilename)
{
	m_pucData = 0;
	if (szFilename != 0)
		Load (szFilename);
}

CImageBMP::~CImageBMP ()
{
	if (m_pucData != 0)
		delete m_pucData;
}

bool CImageBMP::New (unsigned short x, unsigned short y, unsigned char ucTexelSize, unsigned char* pucData)
{
	bool bSuccess = false;

	m_uiSizeX = x;
	m_uiSizeY = y;
	m_unTexelSize = ucTexelSize;

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

bool CImageBMP::Load (const char *szFilename)
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

	FileIn.seekg (0x0000, std::ios::beg);
	FileIn.read ((char*)&m_cIdentifier, sizeof (m_cIdentifier));
	FileIn.seekg (0x000A, std::ios::beg);
	FileIn.read ((char*)&m_uiDataOffset, sizeof (m_uiDataOffset));
	FileIn.seekg (0x0012, std::ios::beg);
	FileIn.read ((char*)&m_uiSizeX, sizeof (m_uiSizeX));
	FileIn.seekg (0x0016, std::ios::beg);
	FileIn.read ((char*)&m_uiSizeY, sizeof (m_uiSizeY));
	FileIn.seekg (0x001C, std::ios::beg);
	FileIn.read ((char*)&m_unTexelSize, sizeof (m_unTexelSize));
	FileIn.seekg (0x001E, std::ios::beg);
	FileIn.read ((char*)&m_uiCompression, sizeof (m_uiCompression));
	FileIn.seekg (0x002E, std::ios::beg);
	FileIn.read ((char*)&m_uiColorsNumber, sizeof (m_uiColorsNumber));

	if (FileIn.fail () || FileIn.bad ())
		return false;

	if (m_cIdentifier[0] != 'B' || m_cIdentifier[1] != 'M')
		return false;

	if (m_uiCompression != 0)
		return false;

	if (m_uiColorsNumber != 0)
		return false;

	unsigned int uiDataSize = m_uiSizeX * m_uiSizeY * m_unTexelSize / 8;

	m_pucData = new unsigned char [uiDataSize];
	if (!m_pucData)
		return false;

	FileIn.seekg (m_uiDataOffset, std::ios::beg);
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

bool CImageBMP::Save ()
{
	if (m_bChanged)
		return SaveAs (m_szFilename.c_str ());
	else
		return true;
}

bool CImageBMP::SaveAs (const char* szFilename)
{
	if (!m_bLoaded && !m_bChanged)
		return false;

	std::ofstream FileOut (szFilename, std::ios::out | std::ios::binary);
	if (!FileOut)
		return false;

	FileOut.seekp (0x0000, std::ios::beg);
	FileOut.write ("BM", 2);
	FileOut.seekp (0x0002, std::ios::beg);
	int iFileSize = 54 + m_uiSizeX * m_uiSizeY * 3;
	FileOut.write ((char*)&iFileSize, 4);
	FileOut.seekp (0x000A, std::ios::beg);
	FileOut.write ((char*)&m_uiDataOffset, sizeof (m_uiDataOffset));
	FileOut.seekp (0x000E, std::ios::beg);
	int iHeaderSize = 0x28;
	FileOut.write ((char*)&iHeaderSize, sizeof (iHeaderSize));
	FileOut.seekp (0x0012, std::ios::beg);
	FileOut.write ((char*)&m_uiSizeX, sizeof (m_uiSizeX));
	FileOut.seekp (0x0016, std::ios::beg);
	FileOut.write ((char*)&m_uiSizeY, sizeof (m_uiSizeY));
	FileOut.seekp (0x001A, std::ios::beg);
	short nPlanes = 1;
	FileOut.write ((char*)&nPlanes, sizeof (nPlanes));
	FileOut.seekp (0x001C, std::ios::beg);
	FileOut.write ((char*)&m_unTexelSize, sizeof (m_unTexelSize));
	FileOut.seekp (0x001E, std::ios::beg);
	FileOut.write ((char*)&m_uiCompression, sizeof (m_uiCompression));
	FileOut.seekp (0x002E, std::ios::beg);
	FileOut.write ((char*)&m_uiColorsNumber, sizeof (m_uiColorsNumber));

	if (FileOut.fail () || FileOut.bad ())
		return false;

	unsigned int uiDataSize = m_uiSizeX * m_uiSizeY * m_unTexelSize / 8;
	FileOut.seekp (m_uiDataOffset, std::ios::beg);
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

unsigned char CImageBMP::GetValue (unsigned short x, unsigned short y, const EColor & Color) const
{
	unsigned char ucValue = 0;
	unsigned char ucTexelSize = m_unTexelSize / 8;

	switch (Color)
	{
	default:
		break;
	case R:
		ucValue = m_pucData[((y * m_uiSizeX) +x) * ucTexelSize + 2];
		break;
	case G:
		ucValue = m_pucData[((y * m_uiSizeX) +x) * ucTexelSize + 1];
		break;
	case B:
		ucValue = m_pucData[((y * m_uiSizeX) +x) * ucTexelSize + 0];
		break;
	case A:
		if ((m_unTexelSize == 16) || (m_unTexelSize == 32))
			ucValue = m_pucData[((y * m_uiSizeX) +x) * ucTexelSize + 3];
		break;
	}

	return ucValue;
}

bool CImageBMP::SetValue (unsigned short x, unsigned short y, const EColor & Color, unsigned char ucValue) 
{
	bool bSuccess = false;
	unsigned char ucTexelSize = m_unTexelSize / 8;

	switch (Color)
	{
	default:
		break;
	case R:
		m_pucData[((y * m_uiSizeX) +x) * ucTexelSize + 2] = ucValue;
		bSuccess = true;
		break;
	case G:
		m_pucData[((y * m_uiSizeX) +x) * ucTexelSize + 1] = ucValue;
		bSuccess = true;
		break;
	case B:
		m_pucData[((y * m_uiSizeX) +x) * ucTexelSize + 0] = ucValue;
		bSuccess = true;
		break;
	case A:
		if ((m_unTexelSize == 16) || (m_unTexelSize == 32))
		{
			m_pucData[((y * m_uiSizeX) +x) * ucTexelSize + 3] = ucValue;
			bSuccess = true;
		}
		break;
	}

	return bSuccess;
}

}; // namespace gtl
