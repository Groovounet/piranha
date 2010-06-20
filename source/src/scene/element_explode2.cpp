//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 21/11/2004
//! \file ./piranha/scene/element_explode2.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_explode2.h"
#include "../particle/index.h"

using namespace scene;

static const float      TIME =                  11.f;

static const char*      TEXTURE_COLORMAP1 =     "./data/planet/colormap1.tga";
static const char*      TEXTURE_COLORMAP2 =     "./data/planet/colormap2.tga";
static const char*      TEXTURE_NORMALMAP =     "./data/planet/normalmap.tga";
static const char*      TEXTURE_LIGHTMAP =      "./data/planet/lightmap.tga";
static const char*      TEXTURE_CLOUDS1 =       "./data/planet/clouds1.tga";
static const char*      TEXTURE_CLOUDS2 =       "./data/planet/clouds2.tga";
static const char*      TEXTURE_FADE1 =         "./data/fade3.tga";

CExplode2::CExplode2 ()
{

}

CExplode2::~CExplode2 ()
{
    file::CManager* pManager = file::CManager::Instance ();

    pManager->DeleteTexture2D (m_pTextureColormap1);
    pManager->DeleteTexture2D (m_pTextureColormap2);
    pManager->DeleteTexture2D (m_pTextureNormalmap);
    pManager->DeleteTexture2D (m_pTextureLightmap);
    pManager->DeleteTexture2D (m_pTextureClouds1);
    pManager->DeleteTexture2D (m_pTextureClouds2);
    pManager->DeleteTexture2D (m_pTextureFade1);

    delete m_pSphere1;
    delete m_pSphere2;
    delete m_pFade1;
}

bool CExplode2::Load ()
{
    file::CManager* pManager = file::CManager::Instance ();

    m_pTextureColormap1 = pManager->CreateTexture2D (TEXTURE_COLORMAP1);
    m_pTextureColormap2 = pManager->CreateTexture2D (TEXTURE_COLORMAP2);
    m_pTextureNormalmap = pManager->CreateTexture2D (TEXTURE_NORMALMAP);
    m_pTextureLightmap = pManager->CreateTexture2D (TEXTURE_LIGHTMAP);
    m_pTextureClouds1 = pManager->CreateTexture2D (TEXTURE_CLOUDS1);
    m_pTextureClouds2 = pManager->CreateTexture2D (TEXTURE_CLOUDS2);
    m_pTextureFade1 = pManager->CreateTexture2D (TEXTURE_FADE1);

    m_uiRay = 0;

    m_pSphere1 = new gl::CObjectDL;
    m_pSphere1->TextureActive (gl::TEXTURE0 | gl::TEXTURE1 | gl::TEXTURE2);
    m_pSphere1->Sphere (1.0f, 24, 24);

    m_pSphere2 = new gl::CObjectDL;
    m_pSphere2->TextureActive (gl::TEXTURE0 | gl::TEXTURE1 | gl::TEXTURE2);
    m_pSphere2->Sphere (1.1f, 24, 24);

    m_pDisk1 = new gl::CObjectDL;
    m_pDisk1->Disk (1.f, 16);

    m_pFade1 = new gl::CFade;
    m_pFade1->Times (7.5f, 10.0f);
    m_pFade1->TextureActive (gl::TEXTURE0);
    m_pFade1->Fade (gl::FADE_IN);
    m_pFade1->Color (gtl::CColor3<float> (1.0f, 1.0f, 1.0f));
    m_pFade1->Init (); 

    return true;
}

void CExplode2::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();
    m_fTimeRay = m_fTimeExplode = 0.f;

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

void CExplode2::End ()
{
    glDisable (GL_LIGHT0);
    glPopAttrib ();
    gl::CCamera::Kill ();
}

bool CExplode2::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CExplode2::Update ()
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;
    particle::CManager::Instance ()->Update ();

    if ((fTime - m_fTimeRay) > 0.1f && m_uiRay < 64)
    {
        SRay Ray;
        m_fTimeRay = fTime;
        Ray.m_fTimeStart = fTime;
        Ray.m_fRotate[0] = gtl::CRand::Float (-180, 180);
        Ray.m_fRotate[1] = gtl::CRand::Float (-180, 180);
        Ray.m_fRotate[2] = gtl::CRand::Float (-180, 180);
        m_Ray.push_back (Ray);
        m_uiRay++;
    }

    if (fTime > TIME / 2.f)
        return;

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
        particle::CExplode::Create (4.f, Position, 0.1f, 8, 1.f, gtl::CColor4<float> (1.0f, 0.5f, 0.2f, 1.0f));
    }
}

void CExplode2::Render () const
{
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;
    if (fTime < 5.f)
    {
        _Render1 (fTime);
    }
    else if (fTime < 10.f)
    {
        _Render2 (fTime);
        //m_pTextureFade1->Bind ();
        //glEnable (GL_TEXTURE_2D);
            m_pFade1->Render (fTime);
        //glDisable (GL_TEXTURE_2D);
    }
    else
    {
        //m_pTextureFade1->Bind ();
        //glEnable (GL_TEXTURE_2D);
            m_pFade1->Render (fTime);
        //glDisable (GL_TEXTURE_2D);
    }
}

void CExplode2::_Render1 (float fTime) const
{
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

        _RenderPlanet (false);
        _RenderRay (fTime);
        glEnable (GL_DEPTH_TEST);
        glDepthMask (GL_FALSE);
            particle::CManager::Instance ()->Render ();
        glDepthMask (GL_TRUE);
        glDisable (GL_DEPTH_TEST);
    glPopMatrix ();
}

void CExplode2::_Render2 (float fTime) const
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity ();

    SDL_WarpMouse (WINDOW_WIDTH >> 1, WINDOW_HEIGHT >> 1);
    gl::CCamera* pCamera = gl::CCamera::Instance ();
    pCamera->LookAt ();

    glEnable (GL_STENCIL_TEST);
        glStencilFunc (GL_ALWAYS, 0x1, 0x1);
        glStencilOp (GL_REPLACE, GL_REPLACE, GL_REPLACE);
        glPushMatrix ();	
            glColor3f (0.0f, 0.0f, 0.0f);
            float fSize = MAX (0, 0.1f * SQR (fTime) - 5.f);
            glRotatef (90, 1, 0, 0);
            //m_pDisk1->Render ();
            GLUquadricObj *pQuadric = gluNewQuadric ();
                gluDisk (pQuadric, 0.0f, MIN (fSize, 1.1f), 16, 1);
            gluDeleteQuadric (pQuadric);
        glPopMatrix ();
        glStencilOp (GL_KEEP, GL_KEEP, GL_KEEP);
    glDisable (GL_STENCIL_TEST);

    glPushMatrix ();
        glRotatef (15.f, 0, 1, 0);

        float Position[] = {0.0f, -1.0f, 0.0f, 0.0f};
        glLightfv (GL_LIGHT0, GL_POSITION, Position);

        glRotatef (15.f, 1, 0, 0);
        glRotatef (60.f + fTime * 36, 0, 0, 1);

        glEnable (GL_STENCIL_TEST);
            glStencilFunc (GL_EQUAL, 0x1, 0x1);
            _RenderPlanet (true);

            glStencilFunc (GL_NOTEQUAL, 0x1, 0x1);
            _RenderPlanet (false);
        glDisable (GL_STENCIL_TEST);

        _RenderRay (fTime);

        glEnable (GL_DEPTH_TEST);
        glDepthMask (GL_FALSE);
            particle::CManager::Instance ()->Render ();
        glDepthMask (GL_TRUE);
        glDisable (GL_DEPTH_TEST);
    glPopMatrix ();
}

EType CExplode2::Type ()
{
    return TYPE_EXPLODE2;
}

bool CExplode2::HUD ()
{
    return true;
}

void CExplode2::_RenderRay (float fTime) const
{
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);

    glEnable (GL_BLEND);
    glEnable (GL_DEPTH_TEST);
        for (std::list<SRay>::const_iterator it = m_Ray.begin (); it != m_Ray.end (); it++)
        {
            glPushMatrix ();
                glRotatef (it->m_fRotate[0], 1, 0, 0);
                glRotatef (it->m_fRotate[1], 0, 1, 0);
                glRotatef (it->m_fRotate[2], 0, 0, 1);
                float fSize = (fTime - it->m_fTimeStart) * 1.0f;
                _RenderCylinder (0.01f + 0.005f * fSize, fSize, 8);
            glPopMatrix ();
        }
    glDisable (GL_DEPTH_TEST);
    glDisable (GL_BLEND);

    glDepthMask (GL_TRUE);
}

void CExplode2::_RenderPlanet (bool bDark) const
{
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_CULL_FACE);
	glEnable (GL_LIGHTING);
    glEnable (GL_TEXTURE_2D);
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
            if (bDark)
                m_pTextureColormap2->Bind ();
            else
                m_pTextureColormap1->Bind ();
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

		glEnable (GL_BLEND);
		glDepthMask (GL_FALSE);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE);
            if (bDark)
                m_pTextureClouds2->Bind ();
            else
                m_pTextureClouds1->Bind ();
            m_pSphere2->Render ();
		glDepthMask (GL_TRUE);
		glDisable (GL_BLEND);
    glDisable (GL_TEXTURE_2D);
    glDisable (GL_LIGHTING);
    glDisable (GL_CULL_FACE);
    glDisable (GL_DEPTH_TEST);
}

void CExplode2::_RenderCylinder (float fRadius, float fLenght, float fDivision) const
{
    float fInc = 2.f * (float)PI / fDivision;

    glBegin (GL_QUADS);
        for (float j = 0.0f; j < 2.f * (float)PI; j += fInc)
        {    
            float x1 = fRadius * sinf (j);
            float y1 = fRadius * cosf (j);
            float x2 = fRadius * sinf (j + fInc);
            float y2 = fRadius * cosf (j + fInc);

            glColor4f (1.0f, 0.5f, 0.3f, 1.0f);
            glVertex3f (x1, y1, 0);
            glColor4f (1.0f, 0.5f, 0.3f, 0.0f);
            glVertex3f (x1, y1, fLenght);
            glColor4f (1.0f, 0.5f, 0.3f, 0.0f);
            glVertex3f (x2, y2, fLenght);
            glColor4f (1.0f, 0.5f, 0.3f, 1.0f);
            glVertex3f (x2, y2, 0);
        }
    glEnd ();
}
