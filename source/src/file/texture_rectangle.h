//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-18-2004
//! \file ./file/texture_rectangle.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_FILE_TEXTURE_RECTANGLE_H__
#define __PIRANHA_FILE_TEXTURE_RECTANGLE_H__

#include "./texture.h"

namespace file {

class CManager;

// 12-18-2004 - NOTE : The function named "Config" MUST be called before create an instance of this class
class CRectangle : public CTexture
{
	friend class CManager;

private:
    static int m_iTextureType;

	void _Load (const char* szFilename);

	CRectangle (const char* szFilename);
	virtual ~CRectangle ();

public:
    static void Config ();

    virtual void Bind () const;
	virtual ETextureType Type () const;
};

}; // file

#endif //__PIRANHA_FILE_TEXTURE_RECTANGLE_H__
