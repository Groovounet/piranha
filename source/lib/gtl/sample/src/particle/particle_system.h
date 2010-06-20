/***********************************************\
	GTL sample
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	particle_system.h, 06/10/2004
\***********************************************/

#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "./particle_element.h"
#include "./timer.h"
#include "./window_sdl.h"

#define PARTICLE_MAX		1024
#define PARTICLE_SIZE		16
#define PARTICLE_TIME		8.f

class CParticleSystem
{
private:
	CParticleElement *m_pElements[PARTICLE_MAX];

	gtl::CVector3<float> m_Position;
	CTimerSDL m_TimerCreate;
	float m_fTime;
	unsigned int m_uiTexture;

	int _FreeIndex () const;

public:
	CParticleSystem ();
	~CParticleSystem ();


	bool Load (const char* szTexture);
	void Update ();
	void Draw () const;
};

#endif //PARTICLE_SYSTEM_H
