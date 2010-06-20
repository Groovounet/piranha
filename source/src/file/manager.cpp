//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./file/manager.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./manager.h"

using namespace file;

CManager::CManager ()
{

}

CManager::~CManager ()
{
    for (TTextures::iterator it = m_Textures.begin (); it != m_Textures.end (); it++)
		delete it->second.second;
}

CTexture2D* CManager::CreateTexture2D (const char* szFilename)
{
    CTexture2D *pTexture = 0;

	TTextures::iterator it = m_Textures.find (szFilename);
	if (it != m_Textures.end ())
	{
		if (it->second.second->Type () == TYPE_TEXTURE_TEXTURE2D)
		{
			pTexture = static_cast<CTexture2D*> (it->second.second);
            it->second.first++;
		}
		else
		{
			pTexture = 0;
		}
	}
	else
	{
		pTexture = new CTexture2D (szFilename);
        m_Textures.insert (std::pair <std::string, TTexturesData> (std::string (szFilename), TTexturesData (1, pTexture)));
	}

	return pTexture;
}

CMipmaps2D* CManager::CreateMipmaps2D (const char* szMipmap1, const char* szMipmap2, const char* szMipmap3, const char* szMipmap4, const char* szMipmap5)
{
    CMipmaps2D *pTexture = 0;

	TTextures::iterator it = m_Textures.find (szMipmap1);
	if (it != m_Textures.end ())
	{
		if (it->second.second->Type () == TYPE_TEXTURE_MIPMAPS2D)
		{
			pTexture = static_cast<CMipmaps2D*>(it->second.second);
            it->second.first++;
		}
		else
		{
			pTexture = 0;
		}
	}
	else
	{
		pTexture = new CMipmaps2D (szMipmap1, szMipmap2, szMipmap3, szMipmap4, szMipmap5);
        // 11-10-2004 NOTE : The idenfier of a custom mipmaped texture is the file name of the first mipmap.
        m_Textures.insert (std::pair <std::string, TTexturesData> (std::string (szMipmap1), TTexturesData (1, pTexture)));
	}

	return pTexture;
}

CRectangle* CManager::CreateRectangle (const char* szFilename)
{
    CRectangle *pTexture = 0;

	TTextures::iterator it = m_Textures.find (szFilename);
	if (it != m_Textures.end ())
	{
		if (it->second.second->Type () == TYPE_TEXTURE_RECTANGLE)
		{
			pTexture = static_cast<CRectangle*> (it->second.second);
            it->second.first++;
		}
		else
		{
			pTexture = 0;
		}
	}
	else
	{
		pTexture = new CRectangle (szFilename);
        m_Textures.insert (std::pair <std::string, TTexturesData> (std::string (szFilename), TTexturesData (1, pTexture)));
	}

	return pTexture;
}

bool CManager::DeleteTexture2D (CTexture* pTexture)
{
	return CManager::Instance ()->_DeleteTexture (pTexture);
}

bool CManager::DeleteMipmaps2D (CTexture* pTexture)
{
	return CManager::Instance ()->_DeleteTexture (pTexture);
}

bool CManager::DeleteRectangle (CTexture* pTexture)
{
	return CManager::Instance ()->_DeleteTexture (pTexture);
}

bool CManager::_DeleteTexture (CTexture* pTexture)
{
    if (!pTexture)
		return false;

	TTextures::iterator it = m_Textures.find (pTexture->GetFilename ());

    it->second.first--;
	if (it->second.first <= 0)
	{
		delete it->second.second;
		m_Textures.erase (it);
	}

	return true;
}
