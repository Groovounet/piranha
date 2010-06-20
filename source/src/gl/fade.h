//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-18-2004
//! \file ./piranha/gl/fade.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_GL_FADE_H__
#define __PIRANHA_GL_FADE_H__

#include "../util/common.h"
#include "../util/tracked.h"
#include "./object_dl.h"

namespace gl {

typedef enum
{
    FADE_IN,
    FADE_OUT
} EFade;

#ifdef DEBUG
class CFade : public util::CTracked<util::TRACKED_FADE>
#else
class CFade
#endif //DEBUG
{
private:
    EFade                       m_Type;
    float                       m_fStart;
    float                       m_fEnd;
    gtl::CVector2<float>        m_Division;
    CObjectDL*                  m_pObject;
    gtl::CColor4<float>         m_Color;

    void                        _RenderLayer (float fTime) const;

public:
                                CFade ();
                                ~CFade ();

    void                        Init ();
    void                        Render (float fTime) const;
    void                        Times (float fStart, float fEnd);
    void                        Fade (const EFade & Fade);
    void                        Division (float x, float y);
    void                        Color (const gtl::CColor3<float> & Color);
    void                        TextureActive (unsigned int uiTexture);
};

}; // gl

#endif //__PIRANHA_GL_FADE_H__
