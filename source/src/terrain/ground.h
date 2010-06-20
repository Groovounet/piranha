//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-26-2004
//! \file ./piranha/terrain/ground.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_TERRAIN_GROUND_H__
#define __PIRANHA_TERRAIN_GROUND_H__

#include "../file/texture.h"
#include "../file/element_terrain.h"
#include "../util/smart.h"
#include "../gl/shader.h"
#include "../gl/object_dl.h"
#include <list>

namespace terrain {

typedef enum
{
	QUAD_NODE_LR = 0, // 27/08/2003 - Lower right
	QUAD_NODE_LL = 1, // 27/08/2003 - Lower left
	QUAD_NODE_UL = 2, // 27/08/2003 - Upper left
	QUAD_NODE_UR = 3  // 27/08/2003 - Upper right
} EQuadNode;

typedef enum
{ 
	QUAD_COMPLETE_FAN = 0,	// 04/09/2003 - Draw complete triangle fan
	QUAD_LL_UR = 5,			// 04/09/2003 - Draw lower left and upper right triangle
	QUAD_LR_UL = 10,		// 04/09/2003 - Draw lower right and upper left triangle
	QUAD_NO_FAN = 15		// 04/09/2003 - Don't draw any triangle
} EQuadDraw;

typedef struct
{
    file::CTexture* m_pTexture;
} SPlantType;

typedef struct
{
    gtl::CVector3<float> m_Position;
    file::CTexture* m_pTexture;
    unsigned int m_uiList;
    SPlantType* m_pType;
    float m_fAngle;
} SPlant;

class CGround
{
private:
    file::CTexture* m_pGroundGood;
    file::CTexture* m_pGroundDark;
    file::CTexture* m_pDetailmap;
    file::CTexture* m_pLightmap;
    file::CTexture* m_pPlantTex;
    std::list<SPlant> m_Plant;
    SPlant* m_pPlant;
    int m_iPlant;
    float m_fPlantLodDistance;
    float m_fPlantHeightMax;
    float m_fPlantHeightMin;
    gl::CShader* m_pShader;
	float m_fScale;
	gtl::CVector3<float>* m_pNormal;
    float* m_pfHeightmap;
    float* m_pfHeightmapBase;
	float* m_pfFogMap;
    unsigned char* m_pucQuadMatrix;
	unsigned short m_unSize;
	float m_fMaxAnisotropy;
	float m_fMinResolution;
	float m_fDesiredResolution;
    std::string m_szMapName;
    unsigned int m_uiVarColorMapGood;
    unsigned int m_uiVarColorMapDark;
    unsigned int m_uiVarDetailMap;
    unsigned int m_uiVarLightMap;
    unsigned int m_uiVarDistortion;
    unsigned int m_uiVarDistance;
    float m_fDetailmapRepeat;

    void _NormalCalculation ();
	unsigned char _GetQuadMatrixData (int x, int y) const;
	void _BuildQuadMatrix ();
	void _SubdivideNode (unsigned short x, unsigned short y, unsigned short unEdgeLength);
	void _RenderVertex (float x, float y, float u, float v) const;
	void _RenderNode (float x, float y, int iEdgeLength) const;
   	void _RenderPlants () const;

    bool _Load (const file::SGround * pGround, const file::SPlants * pPlants, const file::SWater * pWater);
    bool _LoadTextures (const file::SGround * pGround, const file::SPlants * pPlants);
    bool _LoadHeightmap (const file::SGround * pGround);
    bool _LoadShaders (const file::SGround * pGround);
    bool _LoadPlants (const file::SPlants * pPlants, const file::SWater * pWater);

public:
    CGround (const file::SGround * pGround, const file::SPlants * pPlants, const file::SWater * pWater);
    ~CGround ();

    void Render () const;
    void Update ();
    //! 12-30-2004 - Ground distortion at (x, y)
    float Distort (int x, int y);
};

}; // terrain

#endif //__PIRANHA_TERRAIN_GROUND_H__
