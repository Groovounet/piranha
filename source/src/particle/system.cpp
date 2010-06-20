//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-25-2004
//! \file ./particle/system.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./system.h"
#include "../gl/index.h"

using namespace particle;

unsigned int CSystem::m_uiPointSprite = GL_POINT_SPRITE_ARB;

CSystem::CSystem ()
{

}

CSystem::~CSystem ()
{

}

void CSystem::Config ()
{
    if (gl::ARB_point_sprite)
        m_uiPointSprite = GL_POINT_SPRITE_ARB;
    else
        m_uiPointSprite = GL_POINT_SPRITE_NV;
}
