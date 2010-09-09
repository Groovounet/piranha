//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/10/2004
//! \file gtl_image_tga.h
//! \brief Classe CImageTGA, pour le chargement des images TGA.
//////////////////////////////////////////////////////////////////////////////

#ifndef GTL_IMAGE_TGA_H
#define GTL_IMAGE_TGA_H

#include "gtl_image.h"
#include <string>

namespace gtl {

//! \brief Classe pour le chargement des images TGA.
class CImageTGA : public CImage
{
private:
	std::string m_szFilename;
	bool m_bLoaded;
	bool m_bSaved;
	bool m_bChanged;

	unsigned char m_ucIdentificationFieldSize;
	unsigned char m_ucColorMapType;
	unsigned char m_ucImageType;
	unsigned short m_unColorMapOrigin;
	unsigned short m_unColorMapLength;
	unsigned char m_ucColorMapEntrySize;
	unsigned short m_unOriginX;
	unsigned short m_unOriginY;
	unsigned short m_unSizeX;
	unsigned short m_unSizeY;
	unsigned char m_ucTexelSize;
	unsigned char m_ucDescriptor;

	unsigned char* m_pucData;
	char* m_pucIdentificationField;

public:
	CImageTGA (const char* szFilename = 0);
	virtual ~CImageTGA ();

	virtual bool Load (const char* szFilename);
	virtual bool IsLoaded () {return m_bLoaded;}
	virtual bool Save ();
	virtual bool SaveAs (const char* szFilename);
	virtual bool IsSaved () {return m_bSaved;}
	virtual bool New (unsigned short x, unsigned short y, unsigned char ucTexelSize, unsigned char* pucData = 0);

	virtual const unsigned char* Data () const {return m_pucData;}
	virtual unsigned short Width () const {return m_unSizeX;}
	virtual unsigned short Height () const {return m_unSizeY;}
	virtual unsigned char TexelSize () const {return static_cast<unsigned char>(m_ucTexelSize);}

	virtual unsigned char GetValue (unsigned short x, unsigned short y, const EColor & Color) const;
	virtual bool SetValue (unsigned short x, unsigned short y, const EColor & Color, unsigned char ucValue);

	const char* GetIdentificationField () const {return m_pucIdentificationField;}
};

}; //namespace gtl

#endif //GTL_IMAGE_TGA_H
