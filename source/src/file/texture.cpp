//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 10/11/2004
//! \file ./file/texture.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./texture.h"

using namespace file;

CTexture::CTexture ()
{

}

CTexture::~CTexture ()
{

}

unsigned short CTexture::GetWidth () const
{
	return m_unWidth;
}

unsigned short CTexture::GetHeight () const
{
	return m_unHeight;
}

unsigned short CTexture::GetColor () const
{
	return m_ucColor;
}

const char* CTexture::GetFilename () const
{
	return m_szFilename.c_str ();
}

unsigned int CTexture::GetTextureObject () const
{
    return m_uiTexture;
}
