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
        glDeleteObjectARB (m_uiShaderProg);
}

unsigned int CShader::Uniform (const char* szNameVar) const
{
    return glGetUniformLocationARB (m_uiShaderProg, szNameVar);
}

unsigned int CShader::Attrib (const char* szNameVar) const
{
	unsigned int uiAttrib = glGetAttribLocationARB (m_uiShaderProg, szNameVar);
	glBindAttribLocationARB (m_uiShaderProg, uiAttrib, szNameVar);
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
	GLint iResult;
	char szBuffer[BUFFER];
	memset (szBuffer, '\0', BUFFER);

	const char* szShaderSources[2];

	m_uiShaderProg = glCreateProgramObjectARB ();

    // Vertex shader
	szShaderSources[0] = _Load (szVertex);
	GLhandleARB ShaderVert = glCreateShaderObjectARB (GL_VERTEX_SHADER_ARB);
	glShaderSourceARB (ShaderVert, 1, &szShaderSources[0], 0);
	glCompileShaderARB (ShaderVert);
	glAttachObjectARB (m_uiShaderProg, ShaderVert);
    glDeleteObjectARB (ShaderVert);

	// Fragment shader
	szShaderSources[1] = _Load (szPixel);
	GLhandleARB ShaderFrag = glCreateShaderObjectARB (GL_FRAGMENT_SHADER_ARB);
	glShaderSourceARB (ShaderFrag, 1, &szShaderSources[1], 0);
	glCompileShaderARB (ShaderFrag);
	glAttachObjectARB (m_uiShaderProg, ShaderFrag);
    glDeleteObjectARB (ShaderFrag);

	glLinkProgramARB (m_uiShaderProg);

	glGetObjectParameterivARB (m_uiShaderProg, GL_OBJECT_LINK_STATUS_ARB, &iResult);
	if (iResult == GL_FALSE)
	{
		glGetInfoLogARB (m_uiShaderProg, sizeof (szBuffer), 0, szBuffer);
		printf ("%s\n", szBuffer);
		return false;
	}

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
