//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-10-2004
//! \file ./file/texture_mipmaps2d.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./texture_mipmaps2d.h"
#include "../gl/proc.h"
#include "../util/state_machine.h"

using namespace file;

CMipmaps2D::FLoad CMipmaps2D::_Load = 0;

CMipmaps2D::CMipmaps2D (
	const char* szMipmap1,
	const char* szMipmap2,
	const char* szMipmap3,
	const char* szMipmap4,
	const char* szMipmap5)
{
	_Load (this, szMipmap1, szMipmap2, szMipmap3, szMipmap4, szMipmap5);
}

CMipmaps2D::~CMipmaps2D ()
{
	glDeleteTextures (1, &m_uiTexture);
}

void CMipmaps2D::Bind () const
{
	glBindTexture (GL_TEXTURE_2D, m_uiTexture);
}

ETextureType CMipmaps2D::Type () const
{
	return TYPE_TEXTURE_MIPMAPS2D;
}

// 12-18-2004 - NOTE : Using GL_SGIS_mipmaps_generate if the extension is supported
// Else using gluBuild2DMipmaps
void CMipmaps2D::Config ()
{
    if (!gl::SGIS_generate_mipmap)
        _Load = _Load1;
    else
        _Load = _Load2;

    util::CStateMachine::Instance ()->SetConfigured (util::STATE_TEXTURE_MIPMAPS2D, util::CONFIG_DONE);
}

void CMipmaps2D::_Load1 (
    CMipmaps2D* pTexture, 
	const char* szMipmap1,
	const char* szMipmap2,
	const char* szMipmap3,
	const char* szMipmap4,
	const char* szMipmap5)
{
	pTexture->m_szFilename = szMipmap1;

	gtl::CImageTGA Image1 (szMipmap1);
	gtl::CImageTGA Image2 (szMipmap2);
	gtl::CImageTGA Image3 (szMipmap3);
	gtl::CImageTGA Image4 (szMipmap4);
	gtl::CImageTGA Image5 (szMipmap5);
    //gtl::CImageTGA Image6 (szMipmap6);

	glGenTextures (1, &pTexture->m_uiTexture);
	glBindTexture (GL_TEXTURE_2D, pTexture->m_uiTexture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    glHint (GL_GENERATE_MIPMAP_HINT_SGIS, GL_NICEST);

	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, Image1.Width (), Image1.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image1.Data ());
	glTexImage2D (GL_TEXTURE_2D, 1, GL_RGB, Image2.Width (), Image2.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image2.Data ());
	glTexImage2D (GL_TEXTURE_2D, 2, GL_RGB, Image3.Width (), Image3.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image3.Data ());
	glTexImage2D (GL_TEXTURE_2D, 3, GL_RGB, Image4.Width (), Image4.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image4.Data ());
	glTexImage2D (GL_TEXTURE_2D, 4, GL_RGB, Image5.Width (), Image5.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image5.Data ());
}

void CMipmaps2D::_Load2 (
    CMipmaps2D* pTexture, 
	const char* szMipmap1,
	const char* szMipmap2,
	const char* szMipmap3,
	const char* szMipmap4,
	const char* szMipmap5)
{
	pTexture->m_szFilename = szMipmap1;

	gtl::CImageTGA Image1 (szMipmap1);
	gtl::CImageTGA Image2 (szMipmap2);
	gtl::CImageTGA Image3 (szMipmap3);
	gtl::CImageTGA Image4 (szMipmap4);
	gtl::CImageTGA Image5 (szMipmap5);

	glGenTextures (1, &pTexture->m_uiTexture);
	glBindTexture (GL_TEXTURE_2D, pTexture->m_uiTexture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gluBuild2DMipmaps (GL_TEXTURE_2D, 3, Image1.Width (), Image1.Height (), GL_BGR, GL_UNSIGNED_BYTE, Image1.Data ());
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, Image1.Width (), Image1.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image1.Data ());
	glTexImage2D (GL_TEXTURE_2D, 1, GL_RGB, Image2.Width (), Image2.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image2.Data ());
	glTexImage2D (GL_TEXTURE_2D, 2, GL_RGB, Image3.Width (), Image3.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image3.Data ());
	glTexImage2D (GL_TEXTURE_2D, 3, GL_RGB, Image4.Width (), Image4.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image4.Data ());
	//glTexImage2D (GL_TEXTURE_2D, 4, GL_RGB, Image5.Width (), Image5.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image5.Data ());
}

