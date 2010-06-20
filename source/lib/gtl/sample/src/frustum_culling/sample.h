/***********************************************\
	GTL sample : frustum culling
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	sample.h, 02/10/2004
\***********************************************/

#ifndef SAMPLE_H
#define SAMPLE_H

#include "./window_sdl.h"

typedef gtl::CVector3<float> TVector3;
typedef gtl::CVector4<float> TVector4;

#define WINDOW_NAME		"GTL - Frustum Culling"
#define WINDOW_WIDTH	640
#define WINDOW_HEIGHT	480
#define WINDOW_COLOR	32

#define NUM_OBJECTS		250000
#define MOVE_SPEED		0.02f

typedef struct
{
    TVector3 Coord;
    TVector3 Color;

    float fRadius;
} SObjectData;

void Draw ();
bool Begin ();
void End ();
void KeyboardDown (int iKey);
void KeyboardUp (int iKey);

#endif //SAMPLE_H
