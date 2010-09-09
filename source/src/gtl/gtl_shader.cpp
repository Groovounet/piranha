//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// G-Truc Creation, www.g-truc.net
// Sous licence LGPL version 2
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_shader.cpp
//! \brief Classe CShader, pour le chargement des shaders.
//////////////////////////////////////////////////////////////////////////////

#include "gtl_shader.h"
#include <fstream>
#include <string.h>

namespace gtl {

const char* szARBvp1_0 = "!!ARBvp1.0";
const char* szNVvp1_0 = "!!VP1.0";
const char* szNVvp1_1 = "!!VP1.1";
const char* szNVvp2_0 = "!!VP2.0";
const char* szARBfp1_0 = "!!ARBfp1.0";
const char* szNVfp1_0 = "!!FP1.0";

CShader::CShader (const char* szFilename)
{
	m_pcData = 0;
	m_iSize = 0;
	m_bLoaded = false;

	if (szFilename != 0)
		Load (szFilename);
}

CShader::~CShader ()
{
	if (m_bLoaded)
		delete [] m_pcData;
}

/*
bool CShader::Load (const char* szFilename)
{
	if (m_bLoaded)
	{
		delete [] m_pcData;
		m_pcData = 0;
		m_iSize = 0;
		m_bLoaded = false;
	}

	FILE* pFile = fopen (szFilename, "r");
	if (!pFile)
		return false;

	fseek (pFile, 0, SEEK_END);
	m_iSize = ftell (pFile);
	fseek (pFile, 0, SEEK_SET);

	m_pcData = new char [m_iSize + 1];
	memset (m_pcData, '\0', m_iSize + 1);
	if (!m_pcData)
	{
		fclose (pFile);
		return false;
	}

	fread (m_pcData, sizeof (char), m_iSize, pFile);
	fclose (pFile);

	m_bLoaded = true;

	m_iSize = strlen (m_pcData);

	return m_bLoaded;
}
*/

bool CShader::Load (const char* szFilename)
{
	if (m_bLoaded)
	{
		delete [] m_pcData;
		m_pcData = 0;
		m_iSize = 0;
		m_bLoaded = false;
	}

	std::ifstream FileIn (szFilename, std::ios::in);

	FileIn.seekg (0, std::ios::end);
	m_iSize = FileIn.tellg ();
	FileIn.seekg (0, std::ios::beg);

	m_pcData = new char [m_iSize + 1];
	memset (m_pcData, '\0', m_iSize + 1);
	if (!m_pcData)
	{
		FileIn.close ();
		return false;
	}

	FileIn.read (m_pcData, m_iSize);
	FileIn.close ();

	m_bLoaded = true;

	m_iSize = strlen (m_pcData);

	return m_bLoaded;
}

bool CShader::IsShaderType (const char* szType) const
{
	if (!m_bLoaded)
		return false;

	if (strstr (m_pcData, szType) == &m_pcData[0])
		return true;
	else
		return false;
}

bool CShader::IsShaderType (const EShaderType & ShaderType) const
{
	if (!m_bLoaded)
		return false;

	switch (ShaderType)
	{
	default:
	case SHADER_TYPE_NULL:
		return false;
	case SHADER_TYPE_ARB_VP:
		return (strstr (m_pcData, "!!ARBvp1.0") == &m_pcData[0]);
	case SHADER_TYPE_NV_VP:
		return (strstr (m_pcData, "!!VP1.0") == &m_pcData[0]);
	case SHADER_TYPE_NV_VP1_1:
		return (strstr (m_pcData, "!!VP1.1") == &m_pcData[0]);
	case SHADER_TYPE_NV_VP2:
		return (strstr (m_pcData, "!!VP2.0") == &m_pcData[0]);
	case SHADER_TYPE_ARB_FP:
		return (strstr (m_pcData, "!!ARBfp1.0") == &m_pcData[0]);
	case SHADER_TYPE_NV_FP:
		return (strstr (m_pcData, "!!FP1.0") == &m_pcData[0]);
	}
}

EShaderType CShader::GetShaderType () const
{
	if (!m_bLoaded)
		return SHADER_TYPE_NULL;

	if (strstr (m_pcData, "!!ARBvp1.0") == &m_pcData[0])
		return SHADER_TYPE_ARB_VP;
	else if (strstr (m_pcData, "!!VP1.0") == &m_pcData[0])
		return SHADER_TYPE_NV_VP;
	else if (strstr (m_pcData, "!!VP1.1") == &m_pcData[0])
		return SHADER_TYPE_NV_VP1_1;
	else if (strstr (m_pcData, "!!VP2.0") == &m_pcData[0])
		return SHADER_TYPE_NV_VP2;
	else if (strstr (m_pcData, "!!ARBfp1.0") == &m_pcData[0])
		return SHADER_TYPE_ARB_FP;
	else if (strstr (m_pcData, "!!FP1.0") == &m_pcData[0])
		return SHADER_TYPE_NV_FP;
	else
		return SHADER_TYPE_NULL;
}

char* CShader::GetData () const
{
	return m_pcData;
}

long CShader::GetSize () const
{
	return m_iSize;
}

bool CShader::IsLoaded () const
{
	return m_bLoaded;
}

}; // namespace gtl

