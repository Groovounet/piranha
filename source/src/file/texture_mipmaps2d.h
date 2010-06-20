//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 18-12-2004
//! \file ./file/texture_mipmaps2d.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_FILE_TEXTURE_MIPMAPS2D_H__
#define __PIRANHA_FILE_TEXTURE_MIPMAPS2D_H__

#include "./texture.h"

namespace file {

class CManager;

// 12-18-2004 - NOTE : The function named "Config" MUST be called before create an instance of this class
class CMipmaps2D : public CTexture
{
    typedef void (*FLoad) (CMipmaps2D*, const char*, const char*, const char*, const char*, const char*);
	friend class CManager;

private:
    static FLoad _Load;
    static void _Load1 (CMipmaps2D* pTexture, const char* szMipmap1, const char* szMipmap2, const char* szMipmap3, const char* szMipmap4, const char* szMipmap5);
    static void _Load2 (CMipmaps2D* pTexture, const char* szMipmap1, const char* szMipmap2, const char* szMipmap3, const char* szMipmap4, const char* szMipmap5);

	//void _Load (const char* szMipmap1, const char* szMipmap2, const char* szMipmap3, const char* szMipmap4, const char* szMipmap5);

	CMipmaps2D (const char* szMipmap1, const char* szMipmap2, const char* szMipmap3, const char* szMipmap4, const char* szMipmap5);
	virtual ~CMipmaps2D ();

public:
    static void Config ();

    virtual void Bind () const;
	virtual ETextureType Type () const;
};

}; // file

#endif //__PIRANHA_FILE_TEXTURE_MIPMAPS2D_H__
