//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-19-2004
//! \file ./terrain/terrain.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./terrain.h"

using namespace terrain;

CTerrain::CTerrain ()
{
    file::CManager* pManager = file::CManager::Instance ();
    file::CTerrain Element ("./data/xml/terrain.xml");

    m_pGround = new CGround (Element.GetGround (), Element.GetPlants (), Element.GetWater ());
    m_pSky = new CSky (Element.GetSky ());
    m_pWaterObj = new gl::CObjectDL;
    m_pWaterObj->TextureActive (gl::TEXTURE0);
    m_pWaterObj->Plane (gtl::CVector3<float> (0, 0, Element.GetWater ()->m_fHeight), gtl::CVector2<float> (2048, 2048), gtl::CVector2<float> (1, 1));
    m_pWaterTex = pManager->CreateTexture2D (Element.GetWater ()->m_szTexture.c_str ());
}

CTerrain::~CTerrain ()
{
    file::CManager* pManager = file::CManager::Instance ();
    pManager->DeleteTexture2D (m_pWaterTex);

    delete m_pGround;
    delete m_pSky;
    delete m_pWaterObj;
}

void CTerrain::Update ()
{
    m_pGround->Update ();
}

void CTerrain::Render () const
{
/*
    glFogi (GL_FOG_MODE, GL_LINEAR);
    glFogf (GL_FOG_START, 128.f);
    glFogf (GL_FOG_END, 512.f);
    glFogf (GL_FOG_DENSITY, 0.1f);
    glFogfv (GL_FOG_COLOR, gtl::CColor4<float> (0.627f, 0.875f, 1.0f, 1.0f));

    glEnable (GL_FOG);
        glEnable (GL_CULL_FACE);
            m_pGround->Render ();
        glDisable (GL_CULL_FACE);
        m_pSky->Render ();
    glDisable (GL_FOG);
*/
    m_pGround->Render ();
    m_pSky->Render ();

    m_pWaterTex->Bind ();
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    	glDepthMask (GL_FALSE);
        glColor4f (1.0f, 1.0f, 1.0f, 0.5f);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        m_pWaterObj->Render ();
        glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);
    glDisable (GL_TEXTURE_2D);
}

float CTerrain::Distort (int x, int y)
{
    return m_pGround->Distort (x, y);
}

