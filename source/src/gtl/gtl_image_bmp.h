//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/10/2004
//! \file gtl_image_bmp.h
//! \brief Classe CImageBMP, pour le chargement des images BMP.
//////////////////////////////////////////////////////////////////////////////

#ifndef GTL_IMAGE_BMP_H
#define GTL_IMAGE_BMP_H

#include "gtl_image.h"
#include <string>

namespace gtl {

//! \brief Classe pour le chargement des images BMP.
class CImageBMP : public CImage
{
private:
	std::string m_szFilename;
	bool m_bLoaded;
	bool m_bSaved;
	bool m_bChanged;

	char m_cIdentifier [2];
	unsigned int m_uiDataOffset;
	unsigned int m_uiSizeX;
	unsigned int m_uiSizeY;
	unsigned short m_unTexelSize;
	unsigned int m_uiCompression;
	unsigned int m_uiColorsNumber;

	unsigned char* m_pucData;

public:
	CImageBMP (const char* szFilename = 0);
	virtual ~CImageBMP ();

	virtual bool Load (const char* szFilename);
	virtual bool IsLoaded () {return m_bLoaded;}
	virtual bool Save ();
	virtual bool SaveAs (const char* szFilename);
	virtual bool IsSaved () {return m_bSaved;}
	virtual bool New (unsigned short x, unsigned short y, unsigned char ucTexelSize, unsigned char* pucData = 0);

	virtual const unsigned char* Data () const {return m_pucData;}
	virtual unsigned short Width () const {return m_uiSizeX;}
	virtual unsigned short Height () const {return m_uiSizeY;}
	virtual unsigned char TexelSize () const {return static_cast<unsigned char>(m_unTexelSize);}

	virtual unsigned char GetValue (unsigned short x, unsigned short y, const EColor & Color) const;
	virtual bool SetValue (unsigned short x, unsigned short y, const EColor & Color, unsigned char ucValue);
};

}; //namespace gtl

#endif //GTL_IMAGE_BMP_H
