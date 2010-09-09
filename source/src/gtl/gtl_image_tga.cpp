//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_image_tga.cpp
//! \brief Classe CImageTGA, pour le chargement des images TGA.
//////////////////////////////////////////////////////////////////////////////

#include "gtl_image_tga.h"
#include <fstream>

namespace gtl {

CImageTGA::CImageTGA (const char* szFilename)
{
	m_bLoaded = false;
	m_bSaved = false;
	m_bChanged = false;

	m_ucIdentificationFieldSize = 0;
	m_ucColorMapType = 0;
	m_ucImageType = 2;
	m_unColorMapOrigin = 0;
	m_unColorMapLength = 0;
	m_ucColorMapEntrySize = 0;
	m_unOriginX = 0;
	m_unOriginY = 0;
	m_unSizeX = 0;
	m_unSizeY = 0;
	m_ucTexelSize = 24;
	m_ucDescriptor = 0;

	m_pucData = 0;
	m_pucIdentificationField = 0;

	if (szFilename != 0)
		Load (szFilename);
}

CImageTGA::~CImageTGA ()
{
	if (m_pucData != 0)
		delete m_pucData;
	if (m_pucIdentificationField != 0)
		delete m_pucIdentificationField;
}

bool CImageTGA::New (unsigned short x, unsigned short y, unsigned char ucTexelSize, unsigned char* pucData)
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

bool CImageTGA::Load (const char* szFilename)
{
	if (m_bLoaded)
	{
		if (m_pucData != 0)
		{
			delete m_pucData;
			m_pucData = 0;
		}
		if (m_pucIdentificationField != 0)
		{
			delete m_pucIdentificationField;
			m_pucIdentificationField = 0;
		}
		m_bLoaded = false;
	}

	m_szFilename = szFilename;

	std::ifstream FileIn (m_szFilename.c_str (), std::ios::in | std::ios::binary);
	if (!FileIn)
		return false;

	FileIn.read ((char*)&m_ucIdentificationFieldSize, sizeof (m_ucIdentificationFieldSize));
	FileIn.read ((char*)&m_ucColorMapType, sizeof (m_ucColorMapType));
	FileIn.read ((char*)&m_ucImageType, sizeof (m_ucImageType));
	FileIn.read ((char*)&m_unColorMapOrigin, sizeof (m_unColorMapOrigin));
	FileIn.read ((char*)&m_unColorMapLength, sizeof (m_unColorMapLength));
	FileIn.read ((char*)&m_ucColorMapEntrySize, sizeof (m_ucColorMapEntrySize));
	FileIn.read ((char*)&m_unOriginX, sizeof (m_unOriginX));
	FileIn.read ((char*)&m_unOriginY, sizeof (m_unOriginY));
	FileIn.read ((char*)&m_unSizeX, sizeof (m_unSizeX));
	FileIn.read ((char*)&m_unSizeY, sizeof (m_unSizeY));
	FileIn.read ((char*)&m_ucTexelSize, sizeof (m_ucTexelSize));
	FileIn.read ((char*)&m_ucDescriptor, sizeof (m_ucDescriptor));

	if (FileIn.fail () || FileIn.bad ())
		return false;

	switch (m_ucImageType)
	{
	default:
		return false;

	case 2:
		unsigned int uiDataSize = m_unSizeX * m_unSizeY * m_ucTexelSize / 8;

		m_pucData = new unsigned char [uiDataSize];
		if (!m_pucData)
			return false;

		m_pucIdentificationField = new char [m_ucIdentificationFieldSize + 1];
		if (!m_pucIdentificationField)
			return false;

		FileIn.seekg (18 + m_unColorMapLength, std::ios::beg);
		FileIn.read (m_pucIdentificationField, m_ucIdentificationFieldSize);
		m_pucIdentificationField[m_ucIdentificationFieldSize] = '\0';
		FileIn.read ((char*)m_pucData, uiDataSize);

		if (FileIn.fail () || FileIn.bad ())
		{
			delete m_pucData;
			return false;
		}
		else
			m_bLoaded = true;
		break;
	}

	FileIn.close ();

	return m_bLoaded;
}

bool CImageTGA::Save ()
{
	if (m_bChanged)
		return SaveAs (m_szFilename.c_str ());
	else
		return true;
}

bool CImageTGA::SaveAs (const char* szFilename)
{
	if (!m_bLoaded && !m_bChanged)
		return false;

	std::ofstream FileOut (szFilename, std::ios::out | std::ios::binary);
	if (!FileOut)
		return false;

	FileOut.write ((char*)&m_ucIdentificationFieldSize, sizeof (m_ucIdentificationFieldSize));
	FileOut.write ((char*)&m_ucColorMapType, sizeof (m_ucColorMapType));
	FileOut.write ((char*)&m_ucImageType, sizeof (m_ucImageType));
	FileOut.write ((char*)&m_unColorMapOrigin, sizeof (m_unColorMapOrigin));
	FileOut.write ((char*)&m_unColorMapLength, sizeof (m_unColorMapLength));
	FileOut.write ((char*)&m_ucColorMapEntrySize, sizeof (m_ucColorMapEntrySize));
	FileOut.write ((char*)&m_unOriginX, sizeof (m_unOriginX));
	FileOut.write ((char*)&m_unOriginY, sizeof (m_unOriginY));
	FileOut.write ((char*)&m_unSizeX, sizeof (m_unSizeX));
	FileOut.write ((char*)&m_unSizeY, sizeof (m_unSizeY));
	FileOut.write ((char*)&m_ucTexelSize, sizeof (m_ucTexelSize));
	FileOut.write ((char*)&m_ucDescriptor, sizeof (m_ucDescriptor));

	if (FileOut.fail () || FileOut.bad ())
		return false;

	switch (m_ucImageType)
	{
	default:
		m_bSaved = false;
		return false;
	case 2:
		unsigned int uiDataSize = m_unSizeX * m_unSizeY * m_ucTexelSize / 8;
		FileOut.seekp (18 + m_unColorMapLength, std::ios::beg);
		FileOut.write (m_pucIdentificationField, m_ucIdentificationFieldSize);
		FileOut.write ((char*)m_pucData, uiDataSize);
		if (FileOut.fail () || FileOut.bad ())
		{
			delete m_pucData;
			return false;
		}
		else
			m_bSaved = true;
		break;
	}

	FileOut.close ();

	m_bChanged = false;
	return m_bSaved;
}

unsigned char CImageTGA::GetValue (unsigned short x, unsigned short y, const EColor & Color) const
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

bool CImageTGA::SetValue (unsigned short x, unsigned short y, const EColor & Color, unsigned char ucValue) 
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
