//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./gl/shader.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_GL_SHADER_H__
#define __PIRANHA_GL_SHADER_H__

#include "../util/common.h"
#include "../util/tracked.h"

namespace gl {

#ifdef DEBUG
class CShader : public util::CTracked<util::TRACKED_SHADER>
#else
class CShader
#endif //DEBUG
{
private:
    int                     m_uiShaderProg;

    char*                   _Load (const char* szFilename);

public:
                            CShader ();
                            ~CShader ();

    bool                    Load (const char* szVertex, const char* szPixel);
    void                    Enable () const;
    void                    Disable () const;
    unsigned int            Uniform (const char* szNameVar) const;
    unsigned int			Attrib (const char* szNameVar) const;
};

}; // gl

#endif //__PIRANHA_GL_SHADER_H__
