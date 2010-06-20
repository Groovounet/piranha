//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-23-2004
//! \file ./file/element_terrain.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_FILE_ELEMENT_TERRAIN_H__
#define __PIRANHA_FILE_ELEMENT_TERRAIN_H__

#include "./element.h"
#include "../util/common.h"
#include "../tinyxml/tinyxml.h"
#include <string>
#include <vector>

namespace file {

typedef struct
{
    std::string m_szFile;
    float m_fWidth;
    float m_fHeight;
} SPlant;

typedef struct
{
    std::vector<SPlant> m_Plant;
    int m_iPlants;
    float m_fLodDistance;
    float m_fHeightMin;
    float m_fHeightMax;
} SPlants;

typedef struct
{
    float m_fScale;
    float m_fResolutionMin;
    float m_fResolutionDesired;   
    std::string m_szHeightmap;
    std::string m_szColormapGood;
    std::string m_szColormapEvil;
    std::string m_szDetailmap;
    float m_fDetailmapRepeat;
    std::string m_szLightmap;
    std::string m_szShaderFragment;
    std::string m_szShaderVertex;
} SGround;

typedef struct
{
    std::string m_szTexture;
    float m_fHeight;
} SWater;

typedef struct
{
    std::string m_szTexture;
    gtl::CColor3<float> m_Color;
} SSky;

class CTerrain : public CElement
{
private:
    SGround m_Ground;
    SPlants m_Plants;
    SSky m_Sky;
    SWater m_Water;

    void _Load (const char* szFilename);
    void _LoadGround (tixml::Element* pParent);
    void _LoadWater (tixml::Element* pParent);
    void _LoadSky (tixml::Element* pParent);
    void _LoadPlants (tixml::Element* pParent);

public:
    CTerrain (const char* szFilename);

    const SPlants* GetPlants () const;
    const SGround* GetGround () const;
    const SWater* GetWater () const;
    const SSky* GetSky () const;
};

}; // file

#endif //__PIRANHA_FILE_ELEMENT_TERRAIN_H__
