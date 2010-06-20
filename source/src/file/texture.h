//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 10/11/2004
//! \file ./file/texture.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_FILE_TEXTURE_H__
#define __PIRANHA_FILE_TEXTURE_H__

#include "../util/common.h"
#include "../util/tracked.h"
#include <string>

namespace file {

typedef enum
{
	TEXTURE_FORMAT_NULL = 0,
	TEXTURE_FORMAT_TGA,
	TEXTURE_FORMAT_BMP,
	TEXTURE_FORMAT_PNG,
	TEXTURE_FORMAT_JPG,
	TEXTURE_FORMAT_DDS
} ETextureFormat;

typedef enum
{
    TYPE_TEXTURE_NULL = 0,
    TYPE_TEXTURE_TEXTURE2D,
    TYPE_TEXTURE_MIPMAPS2D,
    TYPE_TEXTURE_RECTANGLE
} ETextureType;

class CManager;

#ifdef DEBUG
class CTexture : public util::CTracked<util::TRACKED_TEXTURE>
#else
class CTexture
#endif //DEBUG
{
	friend class CManager;

protected:
	unsigned int m_uiTexture;
	unsigned short m_unWidth;
	unsigned short m_unHeight;
	unsigned char m_ucColor;
	unsigned int m_uiIndex;
	std::string m_szFilename;

	CTexture ();
	virtual ~CTexture ();

public:
    virtual void Bind () const = 0;
	virtual ETextureType Type () const = 0;

	unsigned short GetWidth () const;
	unsigned short GetHeight () const;
	unsigned short GetColor () const;
	const char* GetFilename () const;
    unsigned int GetTextureObject () const;
};

}; // file

#endif //__PIRANHA_FILE_TEXTURE_H__

