//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-11-2004
//! \file ./window/hud.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./hud.h"
#include "../util/timer_global.h"
#include "../util/state_machine.h"

using namespace window;

CHUD::CHUD ()
{

}

CHUD::~CHUD ()
{
    file::CManager* pManager = file::CManager::Instance ();
    pManager->DeleteRectangle (m_pTextureBorder);
    pManager->DeleteMipmaps2D (m_pTextureCube);
    pManager->DeleteTexture2D (m_pTextureCursor);

    delete m_pObject1;
    delete m_pObject2;
}

bool CHUD::Load ()
{
    file::CManager* pManager = file::CManager::Instance ();
    m_pTextureBorder = pManager->CreateRectangle (HUD_TEXTURE);
    m_pTextureCube = pManager->CreateMipmaps2D (HUD_CUBE_MIPMAPS1, HUD_CUBE_MIPMAPS2, HUD_CUBE_MIPMAPS3, HUD_CUBE_MIPMAPS4, HUD_CUBE_MIPMAPS5);
    m_pTextureCursor = pManager->CreateTexture2D (HUD_CURSOR);

    m_pObject1 = new gl::CObjectDL;
    m_pObject1->Cube (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (1, 1, 1));
    m_pObject2 = new gl::CObjectDL;
    m_pObject2->Cube (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (2, 2, 2));

    m_Font.Load (HUD_FONT);
    m_Font.Enable (gtl::FONT_SCALE | gtl::FONT_BLEND);
	m_Font.Color (1.0f, 1.0f, 1.0f);
	m_Font.Size (12.f, 24.f);
    
    glLineWidth (1.f);
    glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);

    m_TimerFps.Init ();
    m_iFpsCount = 0;
    m_iFps = 0;
    m_iFrame = 0;

    return true;
}

void CHUD::ScissorArea (int x, int y, int w, int h)
{
    iScissor[0] = x;
    iScissor[1] = y;
    iScissor[2] = w;
    iScissor[3] = h;
}

void CHUD::Render ()
{
    glPushMatrix ();
        glMatrixMode (GL_PROJECTION);
	    glPushMatrix ();
            glViewport (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
            glMatrixMode (GL_PROJECTION);
		    glLoadIdentity ();
		    glOrtho (0, 640, 0, 480, -1, 1);
		    glMatrixMode (GL_MODELVIEW);
		    glLoadIdentity ();

            _DrawStruct ();
            _DrawInfo ();
            _DrawSpeed ();
            //_DrawMenu ();

            glViewport (6 * WINDOW_WIDTH / 640, 6 * WINDOW_HEIGHT / 480, WINDOW_WIDTH / 10, WINDOW_WIDTH / 10);
            glMatrixMode (GL_PROJECTION);
            glLoadIdentity ();
            gluPerspective (45.f, 1.0f, 0.1f, 512.f);
            glMatrixMode (GL_MODELVIEW);
            glLoadIdentity ();
           	gluLookAt (0, -1.0, 0, 0, 0, 0, 0, 0, 1);

            _DrawTitle ();

            glViewport (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
            glMatrixMode (GL_PROJECTION);
		    glLoadIdentity ();
		    glOrtho (0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
		    glMatrixMode (GL_MODELVIEW);
		    glLoadIdentity ();

            if (util::CStateMachine::Instance ()->Enabled (util::ENABLED_PAUSE))
            {
                _DrawCursor ();
            }

		    glMatrixMode (GL_PROJECTION);
	    glPopMatrix ();
	    glMatrixMode (GL_MODELVIEW);
    glPopMatrix ();
}

void CHUD::Update ()
{
    _CountFps ();
}

void CHUD::_DrawMenu ()
{
    int iMenuOptions = strlen (MENU_OPTIONS) * 12;
    int iMenuConsole = strlen (MENU_CONSOLE) * 12;
    int iMenuSync = strlen (MENU_SYNC) * 12;
    int iMenuPause = strlen (MENU_PAUSE) * 12;
    int iMenuExit = strlen (MENU_EXIT) * 12;
    int iSize = iMenuOptions + iMenuConsole + iMenuSync + iMenuPause + iMenuExit;
    int iSpace = iSize / 6;
    int iOffset = iSpace;

    glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPushMatrix ();
            glTranslated (iOffset, 480 - 28, 0);
            glColor4f (0.f, 0.f, 0.f, 0.25f);
            glBegin (GL_QUADS);
                glVertex2i (0, 0);
                glVertex2i (iMenuOptions, 0);
                glVertex2i (iMenuOptions, 24);
                glVertex2i (0, 24);
            glEnd ();
            glColor4f (0.f, 0.f, 0.f, 0.5f);
            glBegin (GL_LINE_LOOP);
                glVertex2i (0, 0);
                glVertex2i (iMenuOptions, 0);
                glVertex2i (iMenuOptions, 24);
                glVertex2i (0, 24);
            glEnd ();
        glPopMatrix ();
    glDisable (GL_BLEND);

    glPushMatrix ();
        m_Font.Begin ();
            m_Font.Print (iOffset, 480 - 28, MENU_OPTIONS);
            iOffset += iSpace + iMenuOptions;
            m_Font.Print (iOffset, 480 - 28, MENU_CONSOLE);
            iOffset += iSpace + iMenuConsole;
            m_Font.Print (iOffset, 480 - 28, MENU_SYNC);
            iOffset += iSpace + iMenuSync;
            m_Font.Print (iOffset, 480 - 28, MENU_PAUSE);
            iOffset += iSpace + iMenuPause;
            m_Font.Print (iOffset, 480 - 28, MENU_EXIT);
        m_Font.End ();
    glPopMatrix ();
}

void CHUD::_DrawStruct ()
{
    glEnable (GL_TEXTURE_RECTANGLE_ARB);
	glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
        m_pTextureBorder->Bind ();
        glBegin (GL_QUADS);	
		    glTexCoord2f (  0,   0); glVertex2f (  0,   0);
		    glTexCoord2f (640,   0); glVertex2f (640,   0);
		    glTexCoord2f (640, 480); glVertex2f (640, 480); 
		    glTexCoord2f (  0, 480); glVertex2f (  0, 480);
	    glEnd ();
	glDisable (GL_BLEND);
    glDisable (GL_TEXTURE_RECTANGLE_ARB);
}

void CHUD::_DrawCursor ()
{
    glPushMatrix ();
        glTranslated (WINDOW_WIDTH >> 1, WINDOW_HEIGHT >> 1, 0);
        glEnable (GL_BLEND);
        glEnable (GL_TEXTURE_2D);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            m_pTextureCursor->Bind ();
            glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
            glBegin (GL_QUADS);
                glTexCoord2f (0, 0); glVertex2f (-16.f * WINDOW_WIDTH / 640.f,-16.f * WINDOW_HEIGHT / 480.f);
                glTexCoord2f (1, 0); glVertex2f ( 16.f * WINDOW_WIDTH / 640.f,-16.f * WINDOW_HEIGHT / 480.f);
                glTexCoord2f (1, 1); glVertex2f ( 16.f * WINDOW_WIDTH / 640.f, 16.f * WINDOW_HEIGHT / 480.f);
                glTexCoord2f (0, 1); glVertex2f (-16.f * WINDOW_WIDTH / 640.f, 16.f * WINDOW_HEIGHT / 480.f);
            glEnd ();
        glDisable (GL_TEXTURE_2D);
        glDisable (GL_BLEND);
    glPopMatrix (); 
}

void CHUD::_DrawInfo ()
{
    glPushMatrix ();
        m_Font.Begin ();
            m_Font.Print (100, 4, "%.0fs", util::CTimerGlobal::Instance ()->Time ());
            m_Font.Print (200, 4, "%d frames", m_iFrame);
            m_Font.Print (400, 4, "%d fps", m_iFps);
        m_Font.End ();
    glPopMatrix ();
}

void CHUD::_DrawTitle ()
{
    float fTime = util::CTimerGlobal::Instance ()->Time ();
    m_fRotateX = fTime * 10;
    m_fRotateY = fTime * 10;
    m_fRotateZ = fTime * 100;

    //glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
    glPushMatrix ();
        glTranslatef (0, 4.f - cosf (fTime * 4.f) * 4.f, 0);
        glRotatef (cosf (m_fRotateX) * 30.f, 1.0f, 0.0f, 0.0f);
        glRotatef (cosf (m_fRotateY) * 30.f, 0.0f, 1.0f, 0.0f);
		glRotatef (m_fRotateZ, 0.0f, 0.0f, 1.0f);

        m_pTextureCube->Bind ();
        glEnable (GL_TEXTURE_2D);
	        float fBias = -2.4f;
	        float fMaxBias;
	        glGetFloatv (GL_MAX_TEXTURE_LOD_BIAS_EXT, &fMaxBias);
	        if (fabs (fBias) > fMaxBias)
		        fBias = fMaxBias;
	        glTexEnvf (GL_TEXTURE_FILTER_CONTROL_EXT, GL_TEXTURE_LOD_BIAS_EXT, fBias);
            //glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD_SGIS, 0.0);
            //glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD_SGIS, 5.0);
	        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL_SGIS, 0);
	        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL_SGIS, 3);

            glEnable (GL_CULL_FACE);
                glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
                m_pObject1->Render ();
            glDisable (GL_CULL_FACE);
		    glEnable (GL_BLEND);
		    glDepthMask (GL_FALSE);
                glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glColor4f (1.0f, 1.0f, 1.0f, 0.25f);
                m_pObject2->Render ();
		    glDepthMask (GL_TRUE);
		    glDisable (GL_BLEND);
        glDisable (GL_TEXTURE_2D);

/*
        glEnable (GL_TEXTURE_2D);
        glEnable (GL_CULL_FACE);
            m_pTextureCube->Bind ();
	        float fBias = -2.4f;
	        float fMaxBias;
	        glGetFloatv (GL_MAX_TEXTURE_LOD_BIAS_EXT, &fMaxBias);
	        if (fabs (fBias) > fMaxBias)
		        fBias = fMaxBias;
	        glTexEnvf (GL_TEXTURE_FILTER_CONTROL_EXT, GL_TEXTURE_LOD_BIAS_EXT, fBias);
            //glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD_SGIS, 0.0);
            //glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD_SGIS, 5.0);
	        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL_SGIS, 0);
	        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL_SGIS, 3);
            fx::CObjects::Instance ()->Draw (fx::OBJECT_CUBE); //OBJECT_SPHERE
        glDisable (GL_CULL_FACE);
        glDisable (GL_TEXTURE_2D);
*/
    glPopMatrix ();
}

void CHUD::_DrawSpeed ()
{
    static float fSpeedAngle = 0.0f;
    fSpeedAngle += 0.1f;

    glColor4f (0.0f, 0.0f, 0.0f, 1.0f);
    glPushMatrix ();
        glTranslatef (640 - 128 - 6, 15, 0);
        glEnable (GL_LINE_STIPPLE);
            glLineStipple (1, 0x0f0f);
            glBegin (GL_LINES);
                glVertex2i (0, 0);
                glVertex2i (128, 0);
            glEnd ();
        glDisable (GL_LINE_STIPPLE);
        glEnable (GL_LINE_SMOOTH);
        glEnable (GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBegin (GL_LINE_STRIP);
                for (float i = 0; i <= 16; i++)
                    glVertex2f (i * 8, cosf (i / 2.f + fSpeedAngle) * 8.f);
            glEnd ();
        glDisable (GL_BLEND);
        glDisable (GL_LINE_SMOOTH);
    glPopMatrix ();
}

// 14/11/2004 - TODO : Using a local timer in FPS counter
void CHUD::_CountFps ()
{
    m_iFpsCount++;
    m_iFrame++;
    if (m_TimerFps.Time () >= 1.0f)
    {
        m_TimerFps.Init ();
        m_iFps = m_iFpsCount;
        m_iFpsCount = 0;
    }
}
