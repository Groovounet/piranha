//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_font.h
//! \brief Interface CFont, pour l'affichage de caractères.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GTL_FONT_H__
#define __GTL_FONT_H__

#include <stdarg.h>

namespace gtl {

#define FONT_BUFFER 1024

//! \brief Paramètres applicables aux classes héritant de CFont, pour personnaliser l'affichage de caractères.
typedef enum
{
    FONT_NULL       = 0,
    FONT_BLEND      = 1,
    FONT_SCALE      = 2,
    FONT_SPACING    = 4
} EFont;

//! \brief Interface pour l'affichage de caractères.
class CFont
{
protected:
    unsigned int m_uiFontIndex;
    unsigned int m_uiDisplayListIndex;
    bool m_bLoaded;
    unsigned int m_uiOption;
    float m_fScale [3];
    float m_fColor [3];
    float m_fSize [2];
    float m_fSpace;

    virtual void Build () = 0;
public:
    //CFont (const char* szFilename = 0);
    CFont ();
    virtual ~CFont ();
    virtual bool Load (const char* szFilename) = 0;

    void End () const;
    void Begin () const;
    virtual void Print (int x, int y, const char *szMsg, ...) const = 0;
    
    void Enable (unsigned int uiOption);
    void Disable (unsigned int uiOption);
    
    void Size (float x, float y, float z = 1.0f);
    void Color (float x, float y, float z);
    void Spacing (float fSpace);
};

}; // namespace gtl

#endif //__GTL_FONT_H__
