//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-19-2004
//! \file ./terrain/sky.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./sky.h"

using namespace terrain;

CSky::CSky (const file::SSky * pSky)
{
    file::CManager* pManager = file::CManager::Instance ();
    m_pTextureSky1 = pManager->CreateTexture2D (pSky->m_szTexture.c_str ());

    m_pObjectSky1 = new gl::CObjectDL;
    m_pObjectSky1->TextureActive (gl::TEXTURE0);
    m_pObjectSky1->Plane (gtl::CVector3<float> (0, 0, 192), gtl::CVector2<float> (2048, 2048), gtl::CVector2<float> (1, 1));

    m_pObjectSky2 = new gl::CObjectDL;
    //m_pObjectSky2->ColorActive (true);
    //m_pObjectSky2->Color (gtl::CColor4<float> (0.627f, 0.875f, 1.0f, 1.0f));
    m_pObjectSky2->Cylinder (1024.f, 256.f, 12.f, 1.f);

    m_Color = pSky->m_Color;
}

CSky::~CSky ()
{
    file::CManager* pManager = file::CManager::Instance ();
    pManager->DeleteTexture2D (m_pTextureSky1);

    delete m_pObjectSky1;
    delete m_pObjectSky2;
}

void CSky::Render () const
{
    m_pTextureSky1->Bind ();
    glEnable (GL_TEXTURE_2D);
        m_pObjectSky1->Render ();
    glDisable (GL_TEXTURE_2D);
    glColor3fv (m_Color);
    m_pObjectSky2->Render ();
}

