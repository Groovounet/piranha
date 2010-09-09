//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_font_tga.h
//! \brief Classe CFontTGA, pour l'affichage de caractères à partir d'une image TGA.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GTL_FONT_TGA_H__
#define __GTL_FONT_TGA_H__

#include "gtl_font.h"

#include <stdarg.h>

namespace gtl {

//! \brief Classe pour l'affichage de caractères à partir d'une image TGA.
class CFontTGA : public CFont
{
private:
    virtual void Build ();

public:
    CFontTGA (const char* szFilename = 0);
    ~CFontTGA ();
    
    virtual bool Load (const char* szFilename);
    virtual void Print (int x, int y, const char *szMsg, ...) const;
};

}; // namespace gtl

#endif //__GTL_FONT_TGA_H__
