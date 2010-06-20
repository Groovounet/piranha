//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-18-2004
//! \file ./file/texture_texture2d.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./texture_texture2d.h"
#include "../gl/proc.h"
#include "../util/state_machine.h"

using namespace file;

CTexture2D::FLoad CTexture2D::_Load = 0;

CTexture2D::CTexture2D (const char* szFilename)
{
	_Load (this, szFilename);
}

CTexture2D::~CTexture2D ()
{
	glDeleteTextures (1, &m_uiTexture);
}

void CTexture2D::Bind () const
{
	glBindTexture (GL_TEXTURE_2D, m_uiTexture);
}

ETextureType CTexture2D::Type () const
{
	return TYPE_TEXTURE_TEXTURE2D;
}

// 12-18-2004 - NOTE : Using GL_SGIS_mipmaps_generate if the extension is supported
// Else using gluBuild2DMipmaps
void CTexture2D::Config ()
{
    if (!gl::SGIS_generate_mipmap)
        _Load = _Load1;
    else
        _Load = _Load2;

    util::CStateMachine::Instance ()->SetConfigured (util::STATE_TEXTURE_TEXTURE2D, util::CONFIG_DONE);
}

void CTexture2D::_Load1 (CTexture2D* pTexture, const char* szFilename)
{
	pTexture->m_szFilename = szFilename;

	gtl::CImageTGA Image (szFilename);
	glGenTextures (1, &pTexture->m_uiTexture);
	glBindTexture (GL_TEXTURE_2D, pTexture->m_uiTexture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    glHint (GL_GENERATE_MIPMAP_HINT_SGIS, GL_NICEST);

	switch (Image.TexelSize ())
	{
	default:
		break;
	case 24:
    	glTexImage2D (GL_TEXTURE_2D, 0, 3, Image.Width (), Image.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image.Data ());
		break;
	case 32:
		glTexImage2D (GL_TEXTURE_2D, 0, 4, Image.Width (), Image.Height (), 0, GL_BGRA, GL_UNSIGNED_BYTE, Image.Data ());
		break;
	}
}

// gluBuild2DMipmaps
void CTexture2D::_Load2 (CTexture2D* pTexture, const char* szFilename)
{
	pTexture->m_szFilename = szFilename;

	gtl::CImageTGA Image (szFilename);
	glGenTextures (1, &pTexture->m_uiTexture);
	glBindTexture (GL_TEXTURE_2D, pTexture->m_uiTexture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	switch (Image.TexelSize ())
	{
	default:
		break;
	case 24:
        gluBuild2DMipmaps (GL_TEXTURE_2D, 3, Image.Width (), Image.Height (), GL_BGR, GL_UNSIGNED_BYTE, Image.Data ());
		break;
	case 32:
        gluBuild2DMipmaps (GL_TEXTURE_2D, 4, Image.Width (), Image.Height (), GL_BGRA, GL_UNSIGNED_BYTE, Image.Data ());
		break;
	}
}
