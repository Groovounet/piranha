//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/10/2004
//! \file gtl_image.h
//! \brief Interface CImage pour la chargement des images.
//////////////////////////////////////////////////////////////////////////////

#ifndef GTL_IMAGE_H
#define GTL_IMAGE_H

#include "gtl_color.h"

namespace gtl {

//! \brief Classe pour le chargement des images.
class CImage
{
public:
	virtual ~CImage () {}

	virtual bool Load (const char* szFilename) = 0;
	virtual bool IsLoaded () = 0;
	virtual bool Save () = 0;
	virtual bool SaveAs (const char* szFilename) = 0;
	virtual bool IsSaved () = 0;
	virtual bool New (unsigned short x, unsigned short y, unsigned char ucTexelSize, unsigned char* pucData = 0) = 0;

	virtual const unsigned char* Data () const = 0;
	virtual unsigned short Width () const = 0;
	virtual unsigned short Height () const = 0;
	virtual unsigned char TexelSize () const = 0;

	virtual unsigned char GetValue (unsigned short x, unsigned short y, const EColor & Color) const = 0;
	virtual bool SetValue (unsigned short x, unsigned short y, const EColor & Color, unsigned char ucValue) = 0;
};

}; //namespace gtl

#endif //GTL_IMAGE_H
