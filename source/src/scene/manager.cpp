//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 G-Truc Creation
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (http://www.g-truc.net)
//! \date 11-21-2004
//! \file ./scene/manager.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./manager.h"
#include "./element.h"
#include "./element_loading.h"
#include "./element_author.h"
#include "./element_title.h"
#include "./element_fade.h"
#include "./element_tunnel1.h"
#include "./element_tunnel2.h"
#include "./element_tunnel3.h"
#include "./element_tunnel4.h"
#include "./element_tunnel5.h"
#include "./element_tunnel6.h"
#include "./element_tunnel7.h"
#include "./element_tunnel8.h"
#include "./element_terrain1.h"
#include "./element_terrain2.h"
#include "./element_terrain3.h"
#include "./element_terrain4.h"
#include "./element_terrain5.h"
#include "./element_terrain6.h"
#include "./element_terrain7.h"
#include "./element_explode1.h"
#include "./element_explode2.h"
#include "./element_explode3.h"
#include "./element_credits.h"
#include "../window/index.h"

using namespace scene;

CManager::CManager ()
{
    m_iSceneSize = 0;
    m_iSceneIndex = 0;
    m_bFirst = true;
    for (int i = 0; i < SCENE_MAX; i++)
		m_pScene[i] = 0;
}

CManager::~CManager ()
{
	for (int i = 0; i < SCENE_MAX; i++)
		if (m_pScene[i])
			_Kill (i);
}

bool CManager::Load ()
{
    for (int i = 0; i < SCENE_MAX; i++)
    {
        if (m_pScene[i])
        {
            if (!m_pScene[i]->Load ())
                return false;
        }
    }

    // 11-11-2004 - NOTE : It needn't to draw the scene where the HUD mask it.
    glScissor (0, 32, WINDOW_WIDTH, WINDOW_HEIGHT - 64);

    return true;
}

void CManager::Update ()
{
    if (m_iSceneIndex >= SCENE_MAX || !m_pScene[m_iSceneIndex])
        return;
    
    if (m_pScene[m_iSceneIndex]->IsEnd ())
    {
        m_pScene[m_iSceneIndex]->End ();
        m_iSceneIndex++;
        if (!m_pScene[m_iSceneIndex])
            return;
        m_pScene[m_iSceneIndex]->Begin ();
    }

    m_pScene[m_iSceneIndex]->Update ();
    if (m_pScene[m_iSceneIndex]->HUD ())
        window::CHUD::Instance ()->Update ();
}

void CManager::Render () const
{
    if (m_iSceneIndex >= SCENE_MAX || !m_pScene[m_iSceneIndex])
        return;
    
    if (m_pScene[m_iSceneIndex]->HUD ())
    {
        glEnable (GL_SCISSOR_TEST);
            m_pScene[m_iSceneIndex]->Render ();
        glDisable (GL_SCISSOR_TEST);
        window::CHUD::Instance ()->Render ();
    }
    else
    {
        m_pScene[m_iSceneIndex]->Render ();
    }
}

bool CManager::Push (const EType & Type)
{
    m_pScene[m_iSceneSize] = _Create (Type);
    if (!m_pScene[m_iSceneSize])
        return false;

    m_iSceneSize++;
    return true;
}

CElement* CManager::_Create (const EType & Type)
{
    switch (Type)
    {
    default:
    case TYPE_NULL:
        return 0;
    case TYPE_LOADING:
        return new CLoading;
    case TYPE_AUTHOR:
        return new CAuthor;
    case TYPE_TITLE:
        return new CTitle;
    case TYPE_FADE:
        return new CFade;
    case TYPE_TUNNEL1:
        return new CTunnel1;
    case TYPE_TUNNEL2:
        return new CTunnel2;
    case TYPE_TUNNEL3:
        return new CTunnel3;
    case TYPE_TUNNEL4:
        return new CTunnel4;
    case TYPE_TUNNEL5:
        return new CTunnel5;
    case TYPE_TUNNEL6:
        return new CTunnel6;
    case TYPE_TUNNEL7:
        return new CTunnel7;
    case TYPE_TUNNEL8:
        return new CTunnel8;
    case TYPE_TERRAIN1:
        return new CTerrain1;
    case TYPE_TERRAIN2:
        return new CTerrain2;
    case TYPE_TERRAIN3:
        return new CTerrain3;
    case TYPE_TERRAIN4:
        return new CTerrain4;
    case TYPE_TERRAIN5:
        return new CTerrain5;
    case TYPE_TERRAIN6:
        return new CTerrain6;
    case TYPE_TERRAIN7:
        return new CTerrain7;
    case TYPE_EXPLODE1:
        return new CExplode1;
    case TYPE_EXPLODE2:
        return new CExplode2;
    case TYPE_EXPLODE3:
        return new CExplode3;
    case TYPE_CREDITS:
        return new CCredits;
    }
}

void CManager::_Kill (unsigned int uiIndex)
{
	delete m_pScene[uiIndex];
	m_pScene[uiIndex] = 0;
}

int CManager::_FindFreeIndex () const
{
	for (int i = 0; i < SCENE_MAX; i++)
		if (m_pScene[i] == 0)
			return i;
	return -1;
}
