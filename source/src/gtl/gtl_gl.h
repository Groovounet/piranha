//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 22/12/2004
//! \file gtl_gl.h
//! \brief Fichier pour l'utilisation d'OpenGL et ses extensions.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GTL_GL_H__
#define __GTL_GL_H__

#ifdef WIN32
#include <windows.h>
#endif //WIN32

#define GL_GLEXT_LEGACY
/*
#include <GL/gl.h>
#include <GL/glu.h>
*/
#include "./gl/gl.h"
#include "./gl/glu.h"
#include "./gl/glext.h"

bool IsError ();
const char* GetErrorMsg ();

#endif //__GTL_GL_H__
