//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 14/11/2004
//! \file ./scene/element_credits.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_credits.h"

using namespace scene;

static const float      TIME =                  10.f;

CCredits::CCredits ()
{

}

CCredits::~CCredits ()
{

}

bool CCredits::Load ()
{
    return true;
}

void CCredits::Begin ()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
}

void CCredits::End ()
{
    
}

bool CCredits::IsEnd ()
{
    return false;
}

void CCredits::Update ()
{

}

void CCredits::Render () const
{
    glClear (GL_COLOR_BUFFER_BIT);
}

EType CCredits::Type ()
{
    return TYPE_CREDITS;
}

bool CCredits::HUD ()
{
    return true;
}
