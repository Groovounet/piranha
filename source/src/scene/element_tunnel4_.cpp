//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-26-2004
//! \file ./scene/element_tunnel4.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_tunnel4.h"
#include "../particle/index.h"

using namespace scene;

#define MATH_PI									3.1415926535897932f
#define MATH_RADIAN(a)							(((float) a)*MATH_PI/180.0f)

static const float      TIME =                  5.f;
static const float      DISPLACEMENT =          1.f;
static const float      SEGMENTS =              24.f;
static const float      CIRCLES =               16.f;
static const float      MOVE_SPEED1 =           0.2f;
static const float      MOVE_SPEED2 =           0.5f;
static const float      TEXTURE_SPEED =         240.f;
static const float      TEXTURE_DETAIL_X =      1.0f;
static const float      TEXTURE_DETAIL_Y =      4.0f;
static const float      TEXTURE_WRAPPING =      2.0f;
static const char*      TEXTURE_TUNNEL =        "./data/tunnel2.tga";
static const char*      TEXTURE_COLORMAP =      "./data/planet/colormap1.tga";
static const char*      TEXTURE_CLOUDS =        "./data/planet/clouds1.tga";

static gl::CStateManu<3>* g_pStatePlanet = 0;

CTunnel4::CTunnel4 ()
{

}

CTunnel4::~CTunnel4 ()
{
    file::CManager* pManager = file::CManager::Instance ();

    pManager->DeleteTexture2D (m_pTextureTunnel);
    pManager->DeleteTexture2D (m_pTexturePlanet);
    pManager->DeleteTexture2D (m_pTextureClouds);

    delete m_pSphere1;
    delete m_pSphere2;

    delete m_pFade1;
    delete m_pFade2;

    delete g_pStatePlanet;
    g_pStatePlanet = 0;
}

bool CTunnel4::Load ()
{
    file::CManager* pManager = file::CManager::Instance ();

    m_pTextureTunnel = pManager->CreateTexture2D (TEXTURE_TUNNEL);
    m_pTexturePlanet = pManager->CreateTexture2D (TEXTURE_COLORMAP);
    m_pTextureClouds = pManager->CreateTexture2D (TEXTURE_CLOUDS);

    m_pSphere1 = new gl::CObjectDL;
    m_pSphere1->TextureActive (gl::TEXTURE0 | gl::TEXTURE1 | gl::TEXTURE2);
    m_pSphere1->Sphere (1.0f, 24, 24);

    m_pSphere2 = new gl::CObjectDL;
    m_pSphere2->TextureActive (gl::TEXTURE0 | gl::TEXTURE1 | gl::TEXTURE2);
    m_pSphere2->Sphere (1.1f, 24, 24);

    m_pFade1 = new gl::CFade;
    m_pFade1->Times (0.0f, 0.5f);
    m_pFade1->Fade (gl::FADE_OUT);
    m_pFade1->Color (gtl::CColor3<float> (0.0f, 0.0f, 0.0f));
    m_pFade1->Init ();

    m_pFade2 = new gl::CFade;
    m_pFade2->Times (9.75f, 10.0f);
    m_pFade2->Fade (gl::FADE_IN);
    m_pFade2->Color (gtl::CColor3<float> (0.0f, 0.0f, 0.0f));
    m_pFade2->Init ();

    g_pStatePlanet = new gl::CStateManu<3>;
    g_pStatePlanet->Init (0, GL_DEPTH_TEST);
    g_pStatePlanet->Init (1, GL_LIGHTING);
    g_pStatePlanet->Init (2, GL_TEXTURE_2D);

    return true;
}

void CTunnel4::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    particle::CStars::Create (
        3.f, 
        gtl::CVector3<float> (0, 0, 0), 
        256.f,
        2048);

    glShadeModel (GL_SMOOTH);
    glClearColor (0.0f, 0.0f, 0.1f, 0.0f);

	float Ambient[] = {0.3f, 0.3f, 0.3f, 0.3f};
	float Diffuse[] = {0.9f, 0.9f, 0.9f, 0.9f};
	float Specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glLightfv (GL_LIGHT0, GL_AMBIENT, Ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, Diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, Specular);

    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->SetViewDistance (512.f);
    pCamera->Init (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (0, 1, 0));
    pCamera->Move (-2.0f);

	glEnable (GL_LIGHT0);
}

void CTunnel4::End ()
{
    gl::CCamera::Kill ();

    glDisable (GL_LIGHT0);
}

bool CTunnel4::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTunnel4::Update ()
{
    particle::CManager::Instance ()->Update ();
}

void CTunnel4::Render () const
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

    SDL_WarpMouse (WINDOW_WIDTH >> 1, WINDOW_HEIGHT >> 1);
    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->LookAt ();

    glPushMatrix ();
        float fDisplacement = MAX (240 - (24 * fTime), 0);
        glTranslatef (0, fDisplacement, 0);
        float Position[] = {-1.0f, -1.0f, 0.0f, 0.0f};
        glLightfv (GL_LIGHT0, GL_POSITION, Position);
        glPushMatrix ();
            glRotatef (45.f, 1, 0, 0);
            glRotatef (15.f, 0, 1, 0);
            glRotatef (60.f, 0, 0, 1);
            glRotatef (fTime * 36 + 180, 0, 0, 1);
            _RenderPlanet (fTime);
        glPopMatrix ();
    glPopMatrix ();

    {
        gl::CStateAuto<GL_DEPTH_TEST> Enable;
        glDepthMask (GL_FALSE);
            particle::CManager::Instance ()->Render ();
        glDepthMask (GL_TRUE);
    }

    _RenderTunnel (fTime);
    m_pFade1->Render (fTime);
    m_pFade2->Render (fTime);
}

EType CTunnel4::Type ()
{
    return TYPE_TUNNEL1;
}

bool CTunnel4::HUD ()
{
    return true;
}

void CTunnel4::_RenderPlanet (float fTime) const
{
    g_pStatePlanet->Enable ();
        {
            gl::CStateAuto<GL_CULL_FACE> Enable;
            glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
            m_pTexturePlanet->Bind ();
            m_pSphere1->Render ();
        }
        {
            gl::CStateAuto<GL_BLEND> Enable;
		    glDepthMask (GL_FALSE);
                glBlendFunc (GL_SRC_ALPHA, GL_ONE);
                glColor4f (1.0f, 1.0f, 1.0f, 0.25f);
                m_pTextureClouds->Bind ();
                m_pSphere2->Render ();
		    glDepthMask (GL_TRUE);
        }
    g_pStatePlanet->Disable ();
}

void CTunnel4::_RenderTunnel (float fTime) const
{
    float fDisplacementX = 0.0f;
    float fDisplacementY = 0.0f;
    float fIncCercle = 360.0f / SEGMENTS;
    float fTunnelDeplacement = fTime * TEXTURE_SPEED;

	glActiveTextureARB (GL_TEXTURE0_ARB);
	glEnable (GL_TEXTURE_2D);
	m_pTextureTunnel->Bind ();

    gl::CStateAuto<GL_BLEND> Enable;
    //glBlendFunc (GL_SRC_ALPHA, GL_SRC_ALPHA);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc (GL_SRC_ALPHA, GL_SRC_COLOR);
    //glBlendFunc (GL_SRC_COLOR, GL_ONE);

    glPushMatrix ();
        glTranslatef (0, -3, 0);
    for (float i = 0; i < CIRCLES; i += 1.0f)
    {
        fDisplacementX = sinf (MATH_RADIAN (fTunnelDeplacement * MOVE_SPEED1) + i * 0.2f) * 0.2f * fTime / TIME;
        fDisplacementY = cosf (MATH_RADIAN (fTunnelDeplacement * MOVE_SPEED1) + i * 0.2f) * 0.1f * fTime / TIME;
        fDisplacementX -= cosf (MATH_RADIAN (fTunnelDeplacement * MOVE_SPEED2) + i * 0.2f) * 0.2f * fTime / TIME;
        fDisplacementY -= sinf (MATH_RADIAN (fTunnelDeplacement * MOVE_SPEED2) + i * 0.2f) * 0.1f * fTime / TIME;

        glBegin (GL_QUADS);
            for (float p = 0.0f; p < 360.0f; p += fIncCercle * 1)
            {    
                float x1 = sinf (MATH_RADIAN (p));
                float y1 = cosf (MATH_RADIAN (p));
                float x2 = x1 + fDisplacementX;
                float y2 = y1 + fDisplacementY;
                float x3 = sinf (MATH_RADIAN (p + fIncCercle));
                float y3 = cosf (MATH_RADIAN (p + fIncCercle));
                float x4 = x3 + fDisplacementX;
                float y4 = y3 + fDisplacementY;
                
                float u1 = (p * TEXTURE_WRAPPING) / 360.0f;
                float u2 = ((p + fIncCercle) * TEXTURE_WRAPPING) / 360.0f;
                float v1 = (((float) i + 0) * TEXTURE_WRAPPING) / (float) CIRCLES;
                float v2 = (((float) i + 1) * TEXTURE_WRAPPING) / (float) CIRCLES;

                u1 += fTime * 0.2f;
                u2 += fTime * 0.2f;
                v1 += fTime * 2.0f;
                v2 += fTime * 2.0f;

                float fColor1 = ((1 - (i + 0) / CIRCLES) / 2.0f) * MIN (fTime / 2.f, 1.0f);
                float fColor2 = ((1 - (i + 1) / CIRCLES) / 2.0f) * MIN (fTime / 2.f, 1.0f);
                glTexCoord2f (u1 * TEXTURE_DETAIL_X, v1 * TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor1); 
                glVertex3f (x1, 0.0f, y1);

                glTexCoord2f (u1*TEXTURE_DETAIL_X, v2*TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor2); 
                glVertex3f (x2, DISPLACEMENT, y2);

                glTexCoord2f (u2*TEXTURE_DETAIL_X, v2*TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor2); 
                glVertex3f (x4, DISPLACEMENT, y4);

                glTexCoord2f (u2*TEXTURE_DETAIL_X, v1*TEXTURE_DETAIL_Y);
                glColor4f (1.0f, 1.0f, 1.0f, fColor1); 
                glVertex3f (x3, 0.0f, y3);
            }
        glEnd ();
        glTranslatef (fDisplacementX, DISPLACEMENT, fDisplacementY);
    }
    glPopMatrix ();

	glActiveTextureARB (GL_TEXTURE0_ARB);
	glDisable (GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, 0);
}
