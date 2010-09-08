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

unsigned short CTexture::Width () const
{
	return m_unWidth;
}

unsigned short CTexture::Height () const
{
	return m_unHeight;
}

unsigned short CTexture::Color () const
{
	return m_ucColor;
}

const char* CTexture::Filename () const
{
	return m_szFilename.c_str ();
}
