//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./file/manager.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_FILE_MANAGER_H__
#define __PIRANHA_FILE_MANAGER_H__

#include "./texture_texture2d.h"
#include "./texture_mipmaps2d.h"
#include "./texture_rectangle.h"
#include "../window/window_sdl.h"
#include "../util/singleton.h"
#include <map>
#include <string>

namespace file {

class CManager : public util::CSingleton<CManager>
{
    friend class util::CSingleton<CManager>;

    typedef std::string TTexturesIndex;
    typedef std::pair<unsigned int, CTexture*> TTexturesData;
    typedef std::map <TTexturesIndex, TTexturesData> TTextures;

private:
    TTextures m_Textures;

	CManager ();
	~CManager ();

    bool _DeleteTexture (CTexture* pTexture);

public:
    CTexture2D* CreateTexture2D (const char* szFilename);
    CMipmaps2D* CreateMipmaps2D (const char* szMipmap1, const char* szMipmap2, const char* szMipmap3, const char* szMipmap4, const char* szMipmap5);
    CRectangle* CreateRectangle (const char* szFilename);

    bool DeleteTexture2D (CTexture* pTexture);
    bool DeleteMipmaps2D (CTexture* pTexture);
    bool DeleteRectangle (CTexture* pTexture);
};

}; // file

#endif //__PIRANHA_FILE_MANAGER_H__
