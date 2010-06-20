//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_glext.cpp
//! \brief Fichier pour l'utilisation des extensions OpenGL.
//////////////////////////////////////////////////////////////////////////////

#include "../include/gtl_glext.h"
#include <string.h>

namespace gtl {

bool CheckExt (const char* szExtName)
{
    char* szExtList = (char*)glGetString (GL_EXTENSIONS);

    if (!strstr (szExtList, szExtName))
        return false;
    else
        return true;
}

}; // namespace gtl

