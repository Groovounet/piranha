//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 14/11/2004
//! \file ./piranha/scene/element_loading.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_loading.h"
#include <string.h>

using namespace scene;

static const float      TIME =                  1.f;

CLoading::CLoading ()
{

}

CLoading::~CLoading ()
{

}

bool CLoading::Load ()
{
    return true;
}

void CLoading::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    SDL_WarpMouse (WINDOW_WIDTH >> 1, WINDOW_HEIGHT >> 1);

    glShadeModel (GL_SMOOTH);
}

void CLoading::End ()
{
    
}

bool CLoading::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

void CLoading::Update ()
{

}

void CLoading::Render () const
{

}

EType CLoading::Type ()
{
    return TYPE_LOADING;
}

bool CLoading::HUD ()
{
    return false;
}
