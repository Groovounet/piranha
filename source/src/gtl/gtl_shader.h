//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_shader.h
//! \brief Déclaration d'une classe pour le chargement des shaders.
//////////////////////////////////////////////////////////////////////////////

#ifndef GTL_SHADER_H
#define GTL_SHADER_H

namespace gtl {

typedef enum
{
	SHADER_TYPE_NULL = 0,
	SHADER_TYPE_ARB_VP,
	SHADER_TYPE_NV_VP,
	SHADER_TYPE_NV_VP1_1,
	SHADER_TYPE_NV_VP2,
	SHADER_TYPE_ARB_FP,
	SHADER_TYPE_NV_FP
} EShaderType;

//! \brief Classe permettant le chargement des shaders.
class CShader
{
private:
	char *m_pcData;
	long m_iSize;
	bool m_bLoaded;

public:
	CShader (const char* szFilename = 0);
	~CShader ();

	bool Load (const char* szFilename);
	char* GetData () const;
	long GetSize () const;
	bool IsLoaded () const;
	bool IsShaderType (const char* szType) const;
	bool IsShaderType (const EShaderType & ShaderType) const;
	EShaderType GetShaderType () const;
};

}; // namespace gtl

#endif //GTL_SHADER_H
