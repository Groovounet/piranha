//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-21-2004
//! \file ./scene/element_explode1.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_explode1.h"
#include "../particle/index.h"

using namespace scene;

static const float      TIME =                  10.f;

static const char*      TEXTURE_COLORMAP =      "./data/planet/colormap1.tga";
static const char*      TEXTURE_NORMALMAP =     "./data/planet/normalmap.tga";
static const char*      TEXTURE_LIGHTMAP =      "./data/planet/lightmap.tga";
static const char*      TEXTURE_CLOUDS =        "./data/planet/clouds1.tga";

CExplode1::CExplode1 ()
{

}

CExplode1::~CExplode1 ()
{
    file::CManager* pManager = file::CManager::Instance ();

    pManager->DeleteTexture2D (m_pTextureColormap);
    pManager->DeleteTexture2D (m_pTextureNormalmap);
    pManager->DeleteTexture2D (m_pTextureLightmap);
    pManager->DeleteTexture2D (m_pTextureClouds);

    delete m_pSphere1;
    delete m_pSphere2;
    delete m_pFade1;
}

bool CExplode1::Load ()
{
    file::CManager* pManager = file::CManager::Instance ();

    m_pTextureColormap = pManager->CreateTexture2D (TEXTURE_COLORMAP);
    m_pTextureNormalmap = pManager->CreateTexture2D (TEXTURE_NORMALMAP);
    m_pTextureLightmap = pManager->CreateTexture2D (TEXTURE_LIGHTMAP);
    m_pTextureClouds = pManager->CreateTexture2D (TEXTURE_CLOUDS);

    m_pSphere1 = new gl::CObjectDL;
    m_pSphere1->TextureActive (gl::TEXTURE0 | gl::TEXTURE1 | gl::TEXTURE2);
    m_pSphere1->Sphere (1.0f, 24, 24);

    m_pSphere2 = new gl::CObjectDL;
    m_pSphere2->TextureActive (gl::TEXTURE0 | gl::TEXTURE1 | gl::TEXTURE2);
    m_pSphere2->Sphere (1.1f, 24, 24);

    m_pFade1 = new gl::CFade;
    m_pFade1->Times (0.0f, 2.5f);
    m_pFade1->Fade (gl::FADE_OUT);
    m_pFade1->Color (gtl::CColor3<float> (0.5f, 0.2f, 0.0f));
    m_pFade1->Init (); 

    return true;
}

void CExplode1::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();
    m_fTimeExplode = 0.f;
    
    particle::CStars::Create (
        3.f, 
        gtl::CVector3<float> (0, 0, 0), 
        256.f,
        2048);

    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->Enable (gl::CAMERA_FRUSTUM);
    pCamera->SetViewDistance (256.f);
    pCamera->Init (gtl::CVector3<float> (0, 0, 0), gtl::CVector3<float> (0, 0.1f, 0));
    pCamera->Move (-40.f);

    glPushAttrib (GL_ALL_ATTRIB_BITS);

    glShadeModel (GL_SMOOTH);
    glClearColor (0.0f, 0.0f, 0.1f, 0.0f);

	float Ambient[] = {0.3f, 0.3f, 0.3f, 0.3f};
	float Diffuse[] = {0.9f, 0.9f, 0.9f, 0.9f};
	float Specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glLightfv (GL_LIGHT0, GL_AMBIENT, Ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, Diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, Specular);

	glEnable (GL_LIGHT0);
    glClearStencil (0x0);
}

void CExplode1::End ()
{
    glDisable (GL_LIGHT0);
    glPopAttrib ();
    gl::CCamera::Kill ();
}

bool CExplode1::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CExplode1::Update ()
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;
    particle::CManager::Instance ()->Update ();

    if (fTime - m_fTimeExplode > 0.02f)
    {
        m_fTimeExplode = fTime;
        float fRandAngleA = gtl::CRand::Float (0.f, (float)PI);
        float fRandAngleB = gtl::CRand::Float (0.f, 2.f * (float)PI);
		float fRandCosA = cos (fRandAngleA);
		float fRandSinA = sin (fRandAngleA);
		float fRandCosB = cos (fRandAngleB);
		float fRandSinB = sin (fRandAngleB);
		gtl::CVector3<float> Position (fRandSinA * fRandCosB, fRandSinA * fRandSinB, fRandCosA);
        particle::CExplode::Create (4.f * (fTime / TIME), Position, 0.1f * (fTime / TIME), 8, gtl::CRand::Float (0.8f, 1.2f), gtl::CColor4<float> (1.0f, 0.5f, 0.2f, 1.0f));
    }
}

void CExplode1::Render () const
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

    SDL_WarpMouse (WINDOW_WIDTH >> 1, WINDOW_HEIGHT >> 1);
    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->LookAt ();

    glPushMatrix ();
        glRotatef (15.f, 0, 1, 0);

        float Position[] = {0.0f, -1.0f, 0.0f, 0.0f};
        glLightfv (GL_LIGHT0, GL_POSITION, Position);

        glRotatef (15.f, 1, 0, 0);
        glRotatef (60.f + fTime * 36, 0, 0, 1);

        _RenderPlanet ();

        glEnable (GL_DEPTH_TEST);
        glDepthMask (GL_FALSE);
            particle::CManager::Instance ()->Render ();
        glDepthMask (GL_TRUE);
        glDisable (GL_DEPTH_TEST);
    glPopMatrix ();

    //m_pFade1->Render (fTime);
}

EType CExplode1::Type ()
{
    return TYPE_EXPLODE1;
}

bool CExplode1::HUD ()
{
    return true;
}

void CExplode1::_RenderPlanet () const
{
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_CULL_FACE);
	glEnable (GL_LIGHTING);

    glPushAttrib (GL_ALL_ATTRIB_BITS);
        // Normalmap
        glActiveTextureARB (GL_TEXTURE0_ARB);
        glEnable (GL_TEXTURE_2D);
        m_pTextureNormalmap->Bind ();
        glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
        glTexEnvi (GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_DOT3_RGBA_ARB);
        glTexEnvi (GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB);
        glTexEnvi (GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR);
        glTexEnvi (GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE);
        glTexEnvi (GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR);

        // Colormap
        glActiveTextureARB (GL_TEXTURE1_ARB);
        glEnable (GL_TEXTURE_2D);
        m_pTextureColormap->Bind ();
        glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
        glTexEnvi (GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_MODULATE);
        glTexEnvi (GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB);
        glTexEnvi (GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR);
        glTexEnvi (GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE);
        glTexEnvi (GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR);

        // Lightmap
        glActiveTextureARB (GL_TEXTURE2_ARB);
        glEnable (GL_TEXTURE_2D);
        m_pTextureLightmap->Bind ();
        // GL_ARB_texture_end_add
        glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
        glTexEnvi (GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_ADD);
        glTexEnvi (GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB);
        glTexEnvi (GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR);
        glTexEnvi (GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE);
        glTexEnvi (GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR);

        m_pSphere1->Render ();

        glActiveTextureARB (GL_TEXTURE2_ARB);
        glDisable (GL_TEXTURE_2D);
        glActiveTextureARB (GL_TEXTURE1_ARB);
        glDisable (GL_TEXTURE_2D);
        glActiveTextureARB (GL_TEXTURE0_ARB);
        glDisable (GL_TEXTURE_2D);
    glPopAttrib ();

    glEnable (GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glDepthMask (GL_FALSE);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE);
        glColor4f (1.0f, 0.5f, 0.1f, 0.25f);
        m_pTextureClouds->Bind ();
        m_pSphere2->Render ();
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
    glDisable (GL_TEXTURE_2D);

    glDisable (GL_LIGHTING);
    glDisable (GL_CULL_FACE);
    glDisable (GL_DEPTH_TEST);
}
