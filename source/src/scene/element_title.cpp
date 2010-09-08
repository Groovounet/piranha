//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 G-Truc Creation
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net)
//! \date 12-04-2004
//! \file ./scene/element_title.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_title.h"
#include <fstream>

using namespace scene;

#define MESSAGE_BUFFER_SIZE 4096

static const float      TIME =                  10.f;

static const char*      TEXTURE_COLORMAP =      "./data/piranha-color.tga";
static const char*      TEXTURE_LIGHTMAP =      "./data/piranha-light.tga";
static const float      MESH_SIZE_X =           32;
static const float      MESH_SIZE_Y =           24;
static const char*      SHADER_FRAG =           "./data/shader/piranha.frag";
static const char*      SHADER_VERT =           "./data/shader/piranha.vert";

CTitle::CTitle ()
{
    m_iVarTexture1 = -1;
    m_iVarTexture2 = -1;
    m_iVarTime = -1;
}

CTitle::~CTitle ()
{
    file::CManager* pFileManager = file::CManager::Instance ();
    pFileManager->DeleteTexture2D (m_pTexture1);
    pFileManager->DeleteTexture2D (m_pTexture2);

    delete m_pObject;
    delete m_pShader;
}

bool CTitle::Load ()
{
    file::CManager* pFileManager = file::CManager::Instance ();

    m_pTexture1 = pFileManager->CreateTexture2D (TEXTURE_COLORMAP);
    m_pTexture2 = pFileManager->CreateTexture2D (TEXTURE_LIGHTMAP);

    m_pObject = new gl::CObjectDL;
    m_pObject->Plane (
        gtl::CVector3<float> (0, 0, 0), 
        gtl::CVector2<float> (MESH_SIZE_X, MESH_SIZE_Y), 
        gtl::CVector2<float> (MESH_SIZE_X, MESH_SIZE_Y));

    m_pShader = new gl::CShader;
    m_pShader->Load (SHADER_VERT, SHADER_FRAG);
	m_iVarTexture1 = m_pShader->Uniform ("Texture1");
    m_iVarTexture2 = m_pShader->Uniform ("Texture2");
	m_iVarTime = m_pShader->Uniform ("time");

    return true;
}

void CTitle::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    glPushAttrib (GL_ALL_ATTRIB_BITS);

    glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
	glShadeModel (GL_SMOOTH);

    glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
}

void CTitle::End ()
{
    glPopAttrib ();
}

bool CTitle::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CTitle::Update ()
{

}

void CTitle::Render () const
{
    static float fLightAngle = 0;
    fLightAngle += 1.0f;
    float fTime = util::CTimerGlobal::Instance ()->Time () - m_fTimeStart;

    m_pShader->Enable ();

	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity ();
	gluLookAt (0, -36, 0, 0, 0, 0, 0, 0, 1);

	glRotatef (90, 1, 0, 0);

    glActiveTextureARB (GL_TEXTURE0_ARB);
    m_pTexture1->Bind ();
    glActiveTextureARB (GL_TEXTURE1_ARB);
    m_pTexture2->Bind ();

	if (m_iVarTexture1 != -1)
		glUniform1iARB (m_iVarTexture1, 0);
	if (m_iVarTexture2 != -1)
		glUniform1iARB (m_iVarTexture2, 1);
	if (m_iVarTime)
		glUniform1fARB (m_iVarTime, fTime);

	glEnable (GL_CULL_FACE);
        m_pObject->Render ();
	glDisable (GL_CULL_FACE);
/*
    float fValue = 0.0f;
    glGetUniformfvARB (m_pShader->Object (), m_iVarTime, &fValue);
    printf ("Time : %f, Shader value = %f\n", fTime, fValue);
*/
    m_pShader->Disable ();
}

EType CTitle::Type ()
{
    return TYPE_TITLE;
}

bool CTitle::HUD ()
{
    return false;
}
