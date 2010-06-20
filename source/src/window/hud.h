//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-11-2004
//! \file ./window/hud.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_WINDOW_HUD_H__
#define __PIRANHA_WINDOW_HUD_H__

#include "../file/manager.h"
#include "../gl/object_dl.h"
#include "../util/common.h"
#include "../util/singleton.h"
#include "../util/timer_local.h"

namespace window {

#define HUD_CURSOR          "./data/cursor.tga"
#define HUD_TEXTURE         "./data/hud2.tga"
#define HUD_CUBE_MIPMAPS1   "./data/mipmap1.tga"
#define HUD_CUBE_MIPMAPS2   "./data/mipmap2.tga"
#define HUD_CUBE_MIPMAPS3   "./data/mipmap3.tga"
#define HUD_CUBE_MIPMAPS4   "./data/mipmap4.tga"
#define HUD_CUBE_MIPMAPS5   "./data/mipmap5.tga"
#define HUD_FONT            "./data/font.tga"

#define MENU_OPTIONS        "Options"
#define MENU_CONSOLE        "Console"
#define MENU_SYNC           "Sync"
#define MENU_PAUSE          "Pause"
#define MENU_EXIT           "Exit"

class CHUD : public util::CSingleton<CHUD>
{
    friend class util::CSingleton<CHUD>;

private:
    int iScissor [4];
    file::CTexture* m_pTextureBorder;
    file::CTexture* m_pTextureCube;
    file::CTexture* m_pTextureCursor;
    gl::CObjectDL* m_pObject1;
    gl::CObjectDL* m_pObject2;
    int m_iFrame;
    int m_iFps;
    int m_iFpsCount;
    util::CTimerLocal m_TimerFps;
    gtl::CFontTGA m_Font;

    float m_fRotateX;
	float m_fRotateY;
	float m_fRotateZ;

    CHUD ();
	~CHUD ();

    void _CountFps ();
    void _DrawStruct ();
    void _DrawInfo ();
    void _DrawTitle ();
    void _DrawSpeed ();
    void _DrawMenu ();
    void _DrawCursor ();

public:
    void ScissorArea (int x, int y, int w, int h);
    bool Load ();
    void Render ();
    void Update ();
};

}; // window

#endif //__PIRANHA_WINDOW_HUD_H__
