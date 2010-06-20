//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-19-2004
//! \file ./terrain/terrain.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_TERRAIN_TERRAIN_H__
#define __PIRANHA_TERRAIN_TERRAIN_H__

#include "./ground.h"
#include "./sky.h"
#include "../util/smart.h"
#include "../gl/object_dl.h"
#include "../file/manager.h"

namespace terrain {

class CTerrain : public util::CSmart<CTerrain>
{
private:
    friend class util::CSmart<CTerrain>;
    
    CGround* m_pGround;
    CSky* m_pSky;
    gl::CObjectDL* m_pWaterObj;
    file::CTexture* m_pWaterTex;

    CTerrain ();
    ~CTerrain ();

public:
    void Update ();
    void Render () const;
    float Distort (int x, int y);
};

}; // terrain

#endif //__PIRANHA_TERRAIN_TERRAIN_H__
