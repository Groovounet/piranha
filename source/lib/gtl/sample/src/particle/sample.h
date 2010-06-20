/***********************************************\
	GTL sample
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	sample.h, 03/10/2004
\***********************************************/

#ifndef SAMPLE_H
#define SAMPLE_H

#include "./terrain.h"
#include "./particle_system.h"

#define WINDOW_WIDTH	640
#define WINDOW_HEIGHT	480
#define WINDOW_COLOR	32
#define WINDOW_NAME		"GTL - Particles"

extern bool g_bRotZ1;
extern bool g_bRotZ2;
extern bool g_bRotX1;
extern bool g_bRotX2;
extern CTerrain *g_pTerrain;
extern CParticleSystem *g_pSystem;

void Draw ();
bool Init ();
void End ();

#endif //SAMPLE_H
