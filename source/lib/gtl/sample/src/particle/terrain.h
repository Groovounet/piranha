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

#include "./window_sdl.h"

class CTerrain
{
private:
	unsigned short m_unSize;
	unsigned int m_uiTexture;
	unsigned char* m_pucHeightmap;
	gtl::CVector3<float>* m_pNormal;

	void _NormalCalculation ();

public:
	CTerrain ();
	~CTerrain ();

	bool Load (const char* szHeightmap, const char* szTexture);
	void Draw ();
	float Height (gtl::CVector3<float> Position);
	gtl::CVector3<float> Normal (gtl::CVector3<float> Position);
};

#endif //TERRAIN_H
