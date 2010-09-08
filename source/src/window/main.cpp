//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./main.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./main.h"
#include "../scene/index.h"

using namespace window;

CMain::CMain ()
{
    Enable (OPTION_DOUBLEBUFFER);
    //Enable (window::OPTION_ESCAPE_EXIT);
    //Enable (window::OPTION_FULLSCREEN);
    //Enable (window::OPTION_SYNC);
    Config (CONFIG_WIDTH, 640);
    Config (CONFIG_HEIGHT, 480);
    //Config (window::CONFIG_SYNC, 60);
    Config (CONFIG_STENCIL, 8);
    Config (CONFIG_VIEW_DISTANCE, 2048);
    SetName ("Piranha");

    m_bPauseOn = false;
    m_bPauseOff = false;
    m_bMoveUp = false;
    m_bMoveDown = false;
    m_bMoveLeft = false;
    m_bMoveRight = false;
}

CMain::~CMain ()
{

}

void CMain::Begin ()
{
    gl::Init ();
    if (!gl::Check ())
        Exit ();

    util::CStateMachine* pMachine = util::CStateMachine::Instance ();
    pMachine->Init ();
#ifdef DEBUG
    pMachine->Log ();
    if (pMachine->IsError ())
        Exit ();
#else
    if (pMachine->IsError ())
    {
        pMachine->Log ();
        Exit ();
    }
#endif

    m_Timer.Init ();
    _RenderLoading ();

    scene::CManager* pSceneManager = scene::CManager::Instance ();

    pSceneManager->Push (scene::TYPE_LOADING);
    pSceneManager->Push (scene::TYPE_AUTHOR);
    pSceneManager->Push (scene::TYPE_TITLE);
    pSceneManager->Push (scene::TYPE_FADE);
    pSceneManager->Push (scene::TYPE_TUNNEL1);
    pSceneManager->Push (scene::TYPE_TUNNEL2);
    pSceneManager->Push (scene::TYPE_TUNNEL3);
    pSceneManager->Push (scene::TYPE_TUNNEL4);
    pSceneManager->Push (scene::TYPE_TUNNEL5);
    pSceneManager->Push (scene::TYPE_TUNNEL6);
    pSceneManager->Push (scene::TYPE_TUNNEL7);
    pSceneManager->Push (scene::TYPE_TUNNEL8);
    pSceneManager->Push (scene::TYPE_TERRAIN1);
    pSceneManager->Push (scene::TYPE_TERRAIN2);
    pSceneManager->Push (scene::TYPE_TERRAIN3);
    pSceneManager->Push (scene::TYPE_TERRAIN4);
    pSceneManager->Push (scene::TYPE_TERRAIN5);
    pSceneManager->Push (scene::TYPE_TERRAIN6);
    pSceneManager->Push (scene::TYPE_TERRAIN7); 
    pSceneManager->Push (scene::TYPE_EXPLODE1);
    pSceneManager->Push (scene::TYPE_EXPLODE2);
    pSceneManager->Push (scene::TYPE_EXPLODE3);
    pSceneManager->Push (scene::TYPE_CREDITS);

    pSceneManager->Load ();
    window::CHUD::Instance ()->Load ();

    util::CTimerGlobal* pTimer = util::CTimerGlobal::Instance ();
    pTimer->Init ();
    pTimer->Play ();
    m_fKeyTimeStart = pTimer->Time ();
}

void CMain::Update ()
{
    float fTime = m_Timer.Time ();

    if (fTime - m_fKeyTimeStart > 0.02f)
    {
        m_fKeyTimeStart = fTime;
        _Event ();
    }

    scene::CManager::Instance ()->Update ();
}

void CMain::Render ()
{
    scene::CManager::Instance ()->Render ();
}

void CMain::End ()
{
    scene::CManager::Kill ();
}

void CMain::KeyDown (int c)
{
    if (c == 27)
        m_bExit = true;
    else if (c == 'p')
        m_bPauseOn = true;
    else if (c == 's')
        m_bPauseOff = true;
    else if (c == SDLK_UP)
        m_bMoveUp = true;
    else if (c == SDLK_DOWN)
        m_bMoveDown = true;
    else if (c == SDLK_RIGHT)
        m_bMoveRight = true;
    else if (c == SDLK_LEFT)
        m_bMoveLeft = true;
}

void CMain::KeyUp (int c)
{
    if (c == SDLK_UP)
        m_bMoveUp = false;
    else if (c == SDLK_DOWN)
        m_bMoveDown = false;
    else if (c == SDLK_RIGHT)
        m_bMoveRight = false;
    else if (c == SDLK_LEFT)
        m_bMoveLeft = false;
}

void CMain::MouseMotion (int x, int y)
{
    if (util::CStateMachine::Instance ()->Enabled (util::ENABLED_PAUSE))
        gl::CCamera::Instance ()->LookAt (-(x - WINDOW_WIDTH / 2.f), -(y - WINDOW_HEIGHT / 2.f));
}

void CMain::MouseButtonUp (const EMouseButton & Button)
{
    switch (Button)
    {
    default:
    case MOUSE_BUTTON_NULL:
        return;
    case MOUSE_BUTTON_LEFT:
        m_bPauseOn = true;
        return;
    case MOUSE_BUTTON_RIGHT:
        m_bPauseOff = true;
        return;
    case MOUSE_BUTTON_MIDDLE:
        return;
    }
}

void CMain::_Event ()
{
    if (m_bPauseOn)
    {
        util::CTimerGlobal::Instance ()->Play ();
        m_bPauseOn = false;
    }

    if (m_bPauseOff)
    {
        util::CTimerGlobal::Instance ()->Stop ();
        m_bPauseOff = false;
    }

    if (util::CStateMachine::Instance ()->Enabled (util::ENABLED_PAUSE))
    {
        if (m_bMoveUp)
        {
            gl::CCamera::Instance ()->Move (1.f);
        }
        if (m_bMoveDown)
        {
            gl::CCamera::Instance ()->Move (-1.f);
        }
        if (m_bMoveRight)
        {
            gl::CCamera::Instance ()->Strafe (1.f);
        }
        if (m_bMoveLeft)
        {
            gl::CCamera::Instance ()->Strafe (-1.f);
        }
    }

    SDL_WarpMouse (m_unWidth >> 1, m_unHeight >> 1);
}

void CMain::_RenderLoading ()
{
    file::CManager* pManager = file::CManager::Instance ();
    file::CTexture* pTexture = pManager->CreateRectangle ("./data/start.tga");

    glClearColor (0, 0, 0, 0);
    glClear (GL_COLOR_BUFFER_BIT);

    glPushMatrix ();
        glMatrixMode (GL_PROJECTION);
	    glPushMatrix ();
            glViewport (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
            glMatrixMode (GL_PROJECTION);
		    glLoadIdentity ();
		    glOrtho (0, 640, 0, 480, -1, 1);
		    glMatrixMode (GL_MODELVIEW);
		    glLoadIdentity ();

            glEnable (GL_TEXTURE_RECTANGLE_ARB);
                pTexture->Bind ();
                glBegin (GL_QUADS);	
		            glTexCoord2f (  0,   0); glVertex2f (  0,   0);
		            glTexCoord2f (640,   0); glVertex2f (640,   0);
		            glTexCoord2f (640, 480); glVertex2f (640, 480); 
		            glTexCoord2f (  0, 480); glVertex2f (  0, 480);
	            glEnd ();
            glDisable (GL_TEXTURE_RECTANGLE_ARB);

		    glMatrixMode (GL_PROJECTION);
	    glPopMatrix ();
	    glMatrixMode (GL_MODELVIEW);
    glPopMatrix ();

    pManager->DeleteRectangle (pTexture);

    Swap (); 
}

int main (int argc, char *argv[])
{
    CMain ().Run ();

#ifdef DEBUG
    util::CTracker* pTracker = util::CTracker::Instance ();

    printf ("Shaders : %d Created ; %d Deleted ; %d Leaks\n",
        pTracker->Created (util::TRACKED_SHADER),
        pTracker->Deleted (util::TRACKED_SHADER),
        pTracker->Leaked (util::TRACKED_SHADER));

    printf ("Objects : %d Created ; %d Deleted ; %d Leaks\n",
        pTracker->Created (util::TRACKED_OBJECT),
        pTracker->Deleted (util::TRACKED_OBJECT),
        pTracker->Leaked (util::TRACKED_OBJECT));

    printf ("Scenes : %d Created ; %d Deleted ; %d Leaks\n",
        pTracker->Created (util::TRACKED_SCENE),
        pTracker->Deleted (util::TRACKED_SCENE),
        pTracker->Leaked (util::TRACKED_SCENE));

    printf ("Textures : %d Created ; %d Deleted ; %d Leaks\n",
        pTracker->Created (util::TRACKED_TEXTURE),
        pTracker->Deleted (util::TRACKED_TEXTURE),
        pTracker->Leaked (util::TRACKED_TEXTURE));

    printf ("Particles System : %d Created ; %d Deleted ; %d Leaks\n",
        pTracker->Created (util::TRACKED_PARTICLE),
        pTracker->Deleted (util::TRACKED_PARTICLE),
        pTracker->Leaked (util::TRACKED_PARTICLE));

    printf ("State : %d Created ; %d Deleted ; %d Leaks\n",
        pTracker->Created (util::TRACKED_STATE),
        pTracker->Deleted (util::TRACKED_STATE),
        pTracker->Leaked (util::TRACKED_STATE));

    printf ("Fade : %d Created ; %d Deleted ; %d Leaks\n",
        pTracker->Created (util::TRACKED_FADE),
        pTracker->Deleted (util::TRACKED_FADE),
        pTracker->Leaked (util::TRACKED_FADE));

    printf ("Ground : %d Created ; %d Deleted ; %d Leaks\n",
        terrain::CTerrain::Created (),
        terrain::CTerrain::Deleted (),
        terrain::CTerrain::Count ());
 
#endif //DEBUG
    return 0;
}
