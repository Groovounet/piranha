//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_gl.cpp
//! \brief Fichier pour l'utilisation d'OpenGL et ses extensions.
//////////////////////////////////////////////////////////////////////////////

#include "../include/gtl_gl.h"

bool IsError ()
{
	return (glGetError () == GL_NO_ERROR ? false : true);
}

const char* GetErrorMsg ()
{
	int iCodeErreur;
	if ((iCodeErreur = glGetError ()) != GL_NO_ERROR)
	{
		const char* szMsgError = (const char*) gluErrorString (iCodeErreur);
		return szMsgError;
	}
	return 0;
}

