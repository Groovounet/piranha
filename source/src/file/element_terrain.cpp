//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-23-2004
//! \file ./file/element_terrain.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_terrain.h"

using namespace file;

CTerrain::CTerrain (const char* szFilename)
{
    if (szFilename)
        _Load (szFilename);
}

const SGround* CTerrain::GetGround () const
{
    return &m_Ground;
}

const SWater* CTerrain::GetWater () const
{
    return &m_Water;
}

const SSky* CTerrain::GetSky () const
{
    return &m_Sky;
}

const SPlants* CTerrain::GetPlants () const
{
    return &m_Plants;
}

void CTerrain::_Load (const char* szFilename)
{
	tixml::Document Document (szFilename);
	Document.LoadFile ();
/*
	Node* node = 0;
	Element* todoElement = 0;
	Element* itemElement = 0;
*/
	tixml::Element* pRoot = Document.FirstChild ("terrain")->ToElement ();
    _LoadGround (pRoot);
    _LoadWater (pRoot);
    _LoadSky (pRoot);
    _LoadPlants (pRoot);
/*
    Element* pElement = pRoot->FirstChildElement ("ground");

    do
    {
        if (pElement->Text ())
        {

        }
    }
    while (pElement = pElement->NextSiblingElement ());
*/
}

void CTerrain::_LoadGround (tixml::Element* pParent)
{
    tixml::Element* pChild = pParent->FirstChildElement ("ground");
    tixml::CAttribute* pAttribute = pChild->FirstAttribute ();
    
    do
    {
        if (!strcmp ("heightmap", pAttribute->Name ()))
            m_Ground.m_szHeightmap = std::string (pAttribute->Value ());
        else if (!strcmp ("scale", pAttribute->Name ()))
            m_Ground.m_fScale = (float) atof (pAttribute->Value ());
        else if (!strcmp ("reso-min", pAttribute->Name ()))
            m_Ground.m_fResolutionMin = (float) atof (pAttribute->Value ());
        else if (!strcmp ("reso-desired", pAttribute->Name ()))
            m_Ground.m_fResolutionDesired = (float) atof (pAttribute->Value ());
        else if (!strcmp ("colormap-good", pAttribute->Name ()))
            m_Ground.m_szColormapGood = std::string (pAttribute->Value ());
        else if (!strcmp ("colormap-evil", pAttribute->Name ()))
            m_Ground.m_szColormapEvil = std::string (pAttribute->Value ());
        else if (!strcmp ("detailmap", pAttribute->Name ()))
            m_Ground.m_szDetailmap = std::string (pAttribute->Value ());
        else if (!strcmp ("detailrepeat", pAttribute->Name ()))
            m_Ground.m_fDetailmapRepeat = (float) atof (pAttribute->Value ());
        else if (!strcmp ("lightmap", pAttribute->Name ()))
            m_Ground.m_szLightmap = std::string (pAttribute->Value ());
        else if (!strcmp ("shader-vert", pAttribute->Name ()))
            m_Ground.m_szShaderVertex = std::string (pAttribute->Value ());
        else if (!strcmp ("shader-frag", pAttribute->Name ()))
            m_Ground.m_szShaderFragment = std::string (pAttribute->Value ());
    }    
    while (pAttribute = pAttribute->Next ());
}

void CTerrain::_LoadWater (tixml::Element* pParent)
{
    tixml::Element* pChild = pParent->FirstChildElement ("water");
    tixml::CAttribute* pAttribute = pChild->FirstAttribute ();

    do
    {
        if (!strcmp ("file", pAttribute->Name ()))
            m_Water.m_szTexture = std::string (pAttribute->Value ());
        else if (!strcmp ("height", pAttribute->Name ()))
            m_Water.m_fHeight = (float) atof (pAttribute->Value ());
    }    
    while (pAttribute = pAttribute->Next ());
}

void CTerrain::_LoadSky (tixml::Element* pParent)
{
    tixml::Element* pChild = pParent->FirstChildElement ("sky");
    tixml::CAttribute* pAttribute = pChild->FirstAttribute ();

    do
    {
        if (!strcmp ("file", pAttribute->Name ()))
            m_Sky.m_szTexture = std::string (pAttribute->Value ());
        else if (!strcmp ("r", pAttribute->Name ()))
            m_Sky.m_Color (gtl::R) = (float) atof (pAttribute->Value ());
        else if (!strcmp ("g", pAttribute->Name ()))
            m_Sky.m_Color (gtl::G) = (float) atof (pAttribute->Value ());
        else if (!strcmp ("b", pAttribute->Name ()))
            m_Sky.m_Color (gtl::B) = (float) atof (pAttribute->Value ());
    }    
    while (pAttribute = pAttribute->Next ());
}

void CTerrain::_LoadPlants (tixml::Element* pParent)
{
    tixml::Element* pChild = pParent->FirstChildElement ("plants");
    tixml::CAttribute* pAttribute = pChild->FirstAttribute ();

    do
    {
        if (!strcmp ("number", pAttribute->Name ()))
            m_Plants.m_iPlants = atoi (pAttribute->Value ());
        else if (!strcmp ("lod-distance", pAttribute->Name ()))
            m_Plants.m_fLodDistance = (float) atof (pAttribute->Value ());
        else if (!strcmp ("height-min", pAttribute->Name ()))
            m_Plants.m_fHeightMin = (float) atof (pAttribute->Value ());
        else if (!strcmp ("height-max", pAttribute->Name ()))
            m_Plants.m_fHeightMax = (float) atof (pAttribute->Value ());
    }    
    while (pAttribute = pAttribute->Next ());
/*
    pChild = pChild->FirstChildElement ("plant");
    do
    {
        CAttribute* pAttribute = pChild->FirstAttribute ();
        SPlant Plant;
        do
        {
            if (!strcmp ("file", pAttribute->Name ()))
                Plant.m_szFile = std::string (pAttribute->Value ());
            else if (!strcmp ("width", pAttribute->Name ()))
                Plant.m_fWidth = (float) atof (pAttribute->Value ());
            else if (!strcmp ("height", pAttribute->Name ()))
                Plant.m_fHeight = (float) atof (pAttribute->Value ());
        }
        while (pAttribute = pAttribute->Next ());
        m_Plants.m_Plant.push_back (Plant);
    }
    while (pChild = pChild->NextSiblingElement ());
*/
}
