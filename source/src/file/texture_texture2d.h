//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 18-12-2004
//! \file ./file/texture_texture2d.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_FILE_TEXTURE_TEXTURE2D_H__
#define __PIRANHA_FILE_TEXTURE_TEXTURE2D_H__

#include "./texture.h"

namespace file {

class CManager;

// 12-18-2004 - NOTE : The function named "Config" MUST be called before create an instance of this class
// Please call "Config" in the State Machine initialisasion fonction.
class CTexture2D : public CTexture
{
    typedef void (*FLoad) (CTexture2D*, const char*);
    friend class CManager;

private:
    static FLoad _Load;
    static void _Load1 (CTexture2D* pTexture, const char* szFilename);
    static void _Load2 (CTexture2D* pTexture, const char* szFilename);

	CTexture2D (const char* szFilename);
	virtual ~CTexture2D ();

public:
    static void Config ();

    virtual void Bind () const;
	virtual ETextureType Type () const;
};

}; // file

#endif //__PIRANHA_FILE_TEXTURE_TEXTURE2D_H__
