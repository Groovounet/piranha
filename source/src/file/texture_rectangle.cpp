//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-18-2004
//! \file ./file/texture_rectangle.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./texture_rectangle.h"
#include "../gl/proc.h"
#include "../util/state_machine.h"

using namespace file;

int CRectangle::m_iTextureType = 0;

CRectangle::CRectangle (const char* szFilename)
{
	_Load (szFilename);
}

CRectangle::~CRectangle ()
{
	glDeleteTextures (1, &m_uiTexture);
}

void CRectangle::Bind () const
{
	glBindTexture (m_iTextureType, m_uiTexture);
}

ETextureType CRectangle::Type () const
{
	return TYPE_TEXTURE_RECTANGLE;
}

void CRectangle::Config ()
{
    if (gl::ARB_texture_rectangle)
    {
        m_iTextureType = GL_TEXTURE_RECTANGLE_ARB;
        util::CStateMachine::Instance ()->SetConfigured (util::STATE_TEXTURE_RECTANGLE, util::CONFIG_DONE);
    }
    else if (gl::NV_texture_rectangle)
    {
        m_iTextureType = GL_TEXTURE_RECTANGLE_NV;
        util::CStateMachine::Instance ()->SetConfigured (util::STATE_TEXTURE_RECTANGLE, util::CONFIG_DONE);
    }
    else
    {
        util::CStateMachine::Instance ()->SetConfigured (util::STATE_TEXTURE_RECTANGLE, util::CONFIG_FAIL);
    }
}

void CRectangle::_Load (const char* szFilename)
{
	m_szFilename = szFilename;

	gtl::CImageTGA Image (szFilename);
	glGenTextures (1, &m_uiTexture);
	glBindTexture (m_iTextureType, m_uiTexture);
	switch (Image.TexelSize ())
	{
	default:
		break;
	case 24:
		glTexImage2D (m_iTextureType, 0, 3, Image.Width (), Image.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image.Data ());
		break;
	case 32:
		glTexImage2D (m_iTextureType, 0, 4, Image.Width (), Image.Height (), 0, GL_BGRA, GL_UNSIGNED_BYTE, Image.Data ());
		break;
	}
}

