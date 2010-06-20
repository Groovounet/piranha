//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./gl/object.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./object.h"

using namespace gl;

int gl::TEXTURE_MAX = 8;

CObject::CObject ()
{
    m_Color = gtl::CColor4<float> (1.0f, 1.0f, 1.0f, 1.0f);
    m_bColor = false;
    m_Normal = NORMAL_SMOOTH;
    m_Orientation = ORIENTATION_OUTSIDE;
    m_Style = STYLE_FILL;
    m_uiTexture = TEXTURE0;
    for (int i = 0; i < TEXTURE_MAX; i++)
        m_Repeat[i] = gtl::CVector2<float> (1.0f, 1.0f);
}

void CObject::Color (const gtl::CColor4<float> & Color)
{
    m_Color = Color;
}

void CObject::ColorActive (bool bColor)
{
    m_bColor = bColor;
}

void CObject::Normal (const ENormal & Normal)
{
    m_Normal = Normal;
}

void CObject::Orientation (const EOrientation & Orientation)
{
    m_Orientation = Orientation;
}

void CObject::Style (const EStyle & Style)
{
    m_Style = Style;
}

void CObject::TextureActive (unsigned int uiTexture)
{
    m_uiTexture = uiTexture;
}

void CObject::TextureRepeat (const ETexture & Texture, const gtl::CVector2<float> & Repeat)
{
    m_Repeat[Texture] = Repeat;
}
