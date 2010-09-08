//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-06-2004
//! \file ./gl/shader.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./shader.h"
#include "./proc.h"
#include <string.h>
#include <fstream>

using namespace gl;

#define BUFFER 4096

CShader::CShader ()
{
    m_uiShaderProg = -1;
}

CShader::~CShader ()
{
    if (m_uiShaderProg != -1)
        glDeleteProgram(m_uiShaderProg);
}

unsigned int CShader::Uniform (const char* szNameVar) const
{
    return glGetUniformLocation(m_uiShaderProg, szNameVar);
}

unsigned int CShader::Attrib(const char* szNameVar) const
{
	unsigned int uiAttrib = glGetAttribLocation(m_uiShaderProg, szNameVar);
	//glBindAttribLocation(m_uiShaderProg, uiAttrib, szNameVar);
    return uiAttrib;
}

void CShader::Enable () const
{
    glUseProgramObjectARB (m_uiShaderProg);
}

void CShader::Disable () const
{
    glUseProgramObjectARB (0);
}

bool CShader::Load (const char* szVertex, const char* szPixel)
{
	char szBuffer[BUFFER];
	memset (szBuffer, '\0', BUFFER);

	const char* szShaderSources[2];

	m_uiShaderProg = glCreateProgramObjectARB ();

    // Vertex shader
	szShaderSources[0] = _Load (szVertex);
	unsigned int ShaderVert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource (ShaderVert, 1, &szShaderSources[0], 0);
	glCompileShader(ShaderVert);
	glAttachShader(m_uiShaderProg, ShaderVert);
    glDeleteShader(ShaderVert);
	delete[] szShaderSources[0];

	// Fragment shader
	szShaderSources[1] = _Load (szPixel);
	unsigned int ShaderFrag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ShaderFrag, 1, &szShaderSources[1], 0);
	glCompileShader(ShaderFrag);
	glAttachShader(m_uiShaderProg, ShaderFrag);
    glDeleteShader(ShaderFrag);
	delete[] szShaderSources[1];

	glLinkProgram(m_uiShaderProg);
/*
	glGetObjectParameteriv(m_uiShaderProg, GL_OBJECT_LINK_STATUS, &iResult);
	if (iResult == GL_FALSE)
	{
		glGetInfoLogARB (m_uiShaderProg, sizeof (szBuffer), 0, szBuffer);
		printf ("%s\n", szBuffer);
		return false;
	}
*/
    return true;
}

char* CShader::_Load (const char* szFilename)
{
	int m_iSize;
	std::ifstream FileIn (szFilename, std::ios::in);

	FileIn.seekg (0, std::ios::end);
	m_iSize = FileIn.tellg ();
	FileIn.seekg (0, std::ios::beg);

	char *m_pcData = new char [m_iSize + 1];
	memset (m_pcData, '\0', m_iSize + 1);
	if (!m_pcData)
	{
		FileIn.close ();
		return false;
	}

	FileIn.read (m_pcData, m_iSize);
	FileIn.close ();

	return m_pcData;
}
