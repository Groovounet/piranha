//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-19-2004
//! \file ./piranha/terrain/sky.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_TERRAIN_SKY_H__
#define __PIRANHA_TERRAIN_SKY_H__

#include "../gl/object_dl.h"
#include "../file/index.h"

namespace terrain {

class CSky
{
private:
    gl::CObjectDL* m_pObjectSky1;
    gl::CObjectDL* m_pObjectSky2;
    file::CTexture* m_pTextureSky1;
    gtl::CColor3<float> m_Color;

public:
    CSky (const file::SSky * pSky);
    ~CSky ();

    void Render () const;
};

}; // terrain

#endif //__PIRANHA_TERRAIN_SKY_H__
