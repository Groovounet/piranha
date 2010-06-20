//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./piranha/gl/object.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_GL_OBJECT_H__
#define __PIRANHA_GL_OBJECT_H__

#include "./object.h"
#include "../util/common.h"
#include "../util/tracked.h"

namespace gl {

typedef enum
{
    STYLE_NULL,
    STYLE_POINT,
    STYLE_LINE,
    STYLE_FILL
} EStyle;

typedef enum
{
    ORIENTATION_OUTSIDE,
    ORIENTATION_INSIDE
} EOrientation;

typedef enum
{
    NORMAL_NONE,
    NORMAL_FLAT,
    NORMAL_SMOOTH
} ENormal;

typedef enum
{
    TEXTURE0 = 1,
    TEXTURE1 = 2,
    TEXTURE2 = 4,
    TEXTURE3 = 8,
    TEXTURE4 = 16,
    TEXTURE5 = 32,
    TEXTURE6 = 64,
    TEXTURE7 = 128
} ETexture;

extern int TEXTURE_MAX;

#ifdef DEBUG
class CObject : public util::CTracked<util::TRACKED_OBJECT>
#else
class CObject
#endif //DEBUG
{
private:

protected:
    gtl::CColor4<float> m_Color;
    bool m_bColor;
    ENormal m_Normal;
    EOrientation m_Orientation;
    EStyle m_Style;
    unsigned int m_uiTexture;
    gtl::CVector2<float> m_Repeat[8];

public:
    CObject ();
    virtual ~CObject () {}

    void Color (const gtl::CColor4<float> & Color);
    void ColorActive (bool bColor);
    void Normal (const ENormal & Normal);
    void Orientation (const EOrientation & Orientation);
    void Style (const EStyle & Style);
    void TextureActive (unsigned int uiTexture);
    void TextureRepeat (const ETexture & Texture, const gtl::CVector2<float> & Repeat);
};

}; // gl

#endif //__PIRANHA_GL_OBJECT_H__
