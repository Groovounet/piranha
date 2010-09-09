#include "converter.h"
#include "../../src/common/file/texture.h"
#include <stdio.h>

CConverter::CConverter ()
{
	m_pucTextureData = 0;
	m_pucHeightMapData = 0;
	m_pTextureBuffer = 0;
}

CConverter::~CConverter ()
{
	Init ();
}

void CConverter::Init ()
{
	if (m_pucTextureData)
	{
		delete [] m_pucTextureData;
		m_pucTextureData = 0;
	}

	if (m_pucHeightMapData)
	{
		delete [] m_pucHeightMapData;
		m_pucHeightMapData = 0;
	}

	if (m_pTextureBuffer)
	{
		delete [] m_pTextureBuffer;
		m_pTextureBuffer = 0;		
	}
}

void CConverter::Add (const STexture & Texture)
{
	m_Data.push_back (Texture);
}

bool CConverter::Run ()
{
	for (std::list<STexture>::iterator it = m_Data.begin (); it != m_Data.end (); it++)
	{
		if (!LoadHeightmap (it->m_szHeightmap.c_str ()))
			return false;

		if (!LoadGenTex (*it))
			return false;

		if (!CheckTexGenSize ())
			return false;

		if (!BuildTexture (*it))
			return false;

		if (!SaveTexture (it->m_szFilename.c_str ()))
			return false;

		Init ();
	}
	return true;
}

bool CConverter::BuildTexture (const STexture & Texture)
{
	int i = 0, x, y;
	unsigned char iHeight;
	float fTotalRed, fTotalGreen, fTotalBlue;
	float fBlend;
	unsigned int iIndex;
	int iCoef = m_unTextureSizeX/(m_unHeightMapSizeX-1);

	SLevel *pLevel = new SLevel [m_ucTextureNbr];
	if (!pLevel)
		return false;
	
	for (std::list<SLevel>::const_iterator it = Texture.m_Level.begin (); it != Texture.m_Level.end (); it++, i++)
	{
		pLevel[i].m_szFilename = it->m_szFilename;
		pLevel[i].m_ucHeightFullMax = it->m_ucHeightFullMax;
		pLevel[i].m_ucHeightFullMin = it->m_ucHeightFullMin;
		pLevel[i].m_ucHeightNoneMax = it->m_ucHeightNoneMax;
		pLevel[i].m_ucHeightNoneMin = it->m_ucHeightNoneMin;
	}

	m_pucTextureData = new unsigned char[m_unTextureSizeX * m_unTextureSizeY * 3];
	if (!m_pucTextureData)
		return false;

	for (y = 0; y < m_unTextureSizeY; y++)
	{
		for (x = 0; x < m_unTextureSizeX; x++)
		{
			fTotalRed = 0;
			fTotalGreen = 0;
			fTotalBlue = 0;

			iIndex = y/iCoef * m_unHeightMapSizeX + x/iCoef;
			iHeight = m_pucHeightMapData[iIndex];

			for (int i=0; i<m_ucTextureNbr; i++)
			{
				fBlend = FindBlend (pLevel[i], iHeight);
				fTotalRed += m_pTextureBuffer[i].GetData ()[((y * m_unTextureSizeX) +x) * 3+0] * fBlend;
				fTotalGreen += m_pTextureBuffer[i].GetData ()[((y * m_unTextureSizeX) +x) * 3+1] * fBlend;
				fTotalBlue += m_pTextureBuffer[i].GetData ()[((y * m_unTextureSizeX) +x) * 3+2] * fBlend;
			}

			m_pucTextureData[((y * m_unTextureSizeX) +x) * 3+0] = static_cast<unsigned char>(fTotalRed);
			m_pucTextureData[((y * m_unTextureSizeX) +x) * 3+1] = static_cast<unsigned char>(fTotalGreen);
			m_pucTextureData[((y * m_unTextureSizeX) +x) * 3+2] = static_cast<unsigned char>(fTotalBlue);
		}
	}

	delete [] pLevel;
	delete [] m_pTextureBuffer;
	m_pTextureBuffer = 0;

	return true;
}

bool CConverter::BuildTextureRGB ()
{
	unsigned char ucTemp;
	int x, y;

	for (y=0; y<m_unTextureSizeY; y++)
	{
		for (x=0; x<m_unTextureSizeX; x++)
		{
			ucTemp = m_pucTextureData[((y * m_unTextureSizeX) +x) * 3+0];
			m_pucTextureData[((y * m_unTextureSizeX) +x) * 3+0] = m_pucTextureData[((y * m_unTextureSizeX) +x) * 3+2];
			m_pucTextureData[((y * m_unTextureSizeX) +x) * 3+2] = ucTemp;
		}
	}

	return true;
}

bool CConverter::LoadGenTex (const STexture & Texture)
{
	m_ucTextureNbr = Texture.m_Level.size ();

	m_pTextureBuffer = new gtl::CImageTGA [m_ucTextureNbr];

	if (!m_pTextureBuffer)
		return false;

	int iTexLevelIndex = 0;
	
	for (std::list<SLevel>::const_iterator it = Texture.m_Level.begin ();
		it != Texture.m_Level.end ();
		it++, iTexLevelIndex++)
	{
		m_pTextureBuffer[iTexLevelIndex].Load (it->m_szFilename.c_str ());
	}

	return true;
}

float CConverter::FindBlend (const SLevel & Level, unsigned char iHeight)
{
	float fTemp, fBlend = 0.0;

	if (iHeight <= Level.m_ucHeightFullMax && iHeight >= Level.m_ucHeightFullMin)
		fBlend = 1.0;
	else if (iHeight >= Level.m_ucHeightNoneMax)
		fBlend = 0.0;
	else if (iHeight <= Level.m_ucHeightNoneMin)
		fBlend = 0.0;

	else if (iHeight < Level.m_ucHeightFullMin)
	{
		fBlend = ((float)iHeight - Level.m_ucHeightNoneMin)/(Level.m_ucHeightFullMin-Level.m_ucHeightNoneMin);
	}
	else if (iHeight > Level.m_ucHeightFullMax)
	{
		fTemp = (float)Level.m_ucHeightNoneMax - Level.m_ucHeightFullMax;
		fBlend = (fTemp - (iHeight - Level.m_ucHeightFullMax)) / fTemp; 
	}

	return fBlend;
}

bool CConverter::CheckTexGenSize ()
{
	if (!(m_pTextureBuffer[0].GetSizeX () == m_pTextureBuffer[1].GetSizeX () 
		&& m_pTextureBuffer[1].GetSizeX () == m_pTextureBuffer[2].GetSizeX () 
		&& m_pTextureBuffer[2].GetSizeX () == m_pTextureBuffer[3].GetSizeX ()))
		return false;

	if (!(m_pTextureBuffer[0].GetSizeY () == m_pTextureBuffer[1].GetSizeY () 
		&& m_pTextureBuffer[1].GetSizeY () == m_pTextureBuffer[2].GetSizeY () 
		&& m_pTextureBuffer[2].GetSizeY () == m_pTextureBuffer[3].GetSizeY ()))
		return false;

	m_unTextureSizeX = m_pTextureBuffer[0].GetSizeX ();
	m_unTextureSizeY = m_pTextureBuffer[0].GetSizeY ();

	return true;
}

bool CConverter::LoadHeightmap (const char* szFileName)
{
	gtl::CImageTGA Image (szFileName);
	m_unHeightMapSizeX = Image.GetSizeX ();
	m_unHeightMapSizeY = Image.GetSizeY ();
	m_pucHeightMapData = new unsigned char[m_unHeightMapSizeX * m_unHeightMapSizeY];

	for (int i=0; i<(m_unHeightMapSizeX * m_unHeightMapSizeY); i++)	
		m_pucHeightMapData[i] = Image.GetData ()[i*3];

	return true;
}

bool CConverter::SaveTexture (const char* szFileName)
{
	gtl::CImageTGA ImageFinal;

	ImageFinal.SetSizeX (m_unTextureSizeX);
	ImageFinal.SetSizeY (m_unTextureSizeY);
	ImageFinal.SetTexelSize (24);
	ImageFinal.SetData (m_pucTextureData);
	ImageFinal.SaveAs (szFileName);

	return true;
}

