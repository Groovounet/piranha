/***********************************************\
	GTL sample
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	particle_element.h, 06/10/2004
\***********************************************/

#ifndef PARTICLE_ELEMENT_H
#define PARTICLE_ELEMENT_H

#include "./window_sdl.h"
#include "./timer.h"

class CParticleSystem;

class CParticleElement
{
private:
	friend class CParticleSystem;

	CTimerSDL m_TimeLife;
	CTimerSDL m_TimeMove;
	float m_fTime;
	gtl::CVector3<float> m_Position;
	gtl::CVector3<float> m_Speed;
	gtl::CVector3<float> m_Acceleration;
	gtl::CColor4<float> m_Color;

	CParticleElement (
		const gtl::CVector3<float> & Position,
		float fTime);
	~CParticleElement ();

public:
	gtl::CVector3<float> Position () const;
	gtl::CVector3<float> Speed () const;
	gtl::CColor4<float> Color () const;
	bool IsEnd () const;
};

#endif //PARTICLE_ELEMENT_H
