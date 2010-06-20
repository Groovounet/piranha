/***********************************************\
	GTL sample
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	terrain.h, 03/10/2004
\***********************************************/

#ifndef TERRAIN_H
#define TERRAIN_H

#include "./sample.h"

typedef gtl::CVector3<float> CVector;
typedef gtl::CColor4<float> CColor;

class CTerrain
{
private:
	unsigned short m_unSize;
	unsigned int m_uiTexture;
	unsigned char* m_pucHeightmap;
	CVector* m_pNormal;

	void _NormalCalculation ();

public:
	CTerrain ();
	~CTerrain ();

	bool Load (const char* szHeightmap, const char* szTexture);
	void Draw ();
};

#endif //TERRAIN_H
