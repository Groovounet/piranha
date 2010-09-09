//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_screenshot.h
//! \brief Classe CScreenshot, pour la capture d'écran.
//////////////////////////////////////////////////////////////////////////////

#include <string>

namespace gtl {

//! \brief Classe permettant la capture d'écran.
class CScreenshot
{
private:
	int m_iIndex;
	std::string m_szFilename;
	int m_iWidth;
	int m_iHeight;
	int m_iOriginX;
	int m_iOriginY;
	bool m_bIsConfigurated;

public:
	CScreenshot (const char* szFilename = 0);
	CScreenshot (int iOriginX, int iOriginY, int iWidth, int iHeight, const char* szFilename = 0);
	
	void Config (int iOriginX, int iOriginY, int iWidth, int iHeight);
	bool Snap (const char* szFilename = 0);
};

}; // namespace gtl
