/***********************************************\
	GTL sample
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	particle_element.cpp, 06/10/2004
\***********************************************/

#include "./particle_element.h"

CParticleElement::CParticleElement (
	const gtl::CVector3<float> & Position,
	float fTime)
{
	m_Position = Position;
	float fAngle = gtl::CRand::Float (0.0f, 2 * static_cast<float>(PI));
	float fNorm = gtl::CRand::Float (0.0f, 96.f);
	m_Speed = gtl::CVector3<float>(cosf (fAngle) * fNorm, sinf (fAngle) * fNorm, -32.f);
	m_Acceleration = gtl::CVector3<float>(0.0f, 0.0f, -10.0f);
	m_fTime = fTime;
	m_TimeLife.Init ();
	m_TimeMove.Init ();

	gtl::CColor4<float> ColorRand (
		gtl::CRand::Float (0.5f, 1.0f),
		gtl::CRand::Float (0.5f, 1.0f),
		gtl::CRand::Float (0.5f, 1.0f),
		0.5f);
	float fColorNorm = 1.0f;//ColorRand (gtl::R) + ColorRand (gtl::G) + ColorRand (gtl::B);
	m_Color = gtl::CColor4<float>(
		ColorRand (gtl::R) / fColorNorm, 
		ColorRand (gtl::G) / fColorNorm, 
		ColorRand (gtl::B) / fColorNorm,
		0.5f);

//	m_Color = gtl::CColor4<float>(1.0f, 1.0f, 1.0f, 1.0f);
}

CParticleElement::~CParticleElement ()
{

}

gtl::CVector3<float> CParticleElement::Position () const
{
	// Détermine une durée c'est à dire la différence entre le temps initiale et le temps finale (t - to)
	float fTime = m_TimeMove.GetTime ();
	// Détermine la vitesse : v(t) = a(t)*(t-to) + v0
	gtl::CVector3<float> SpeedF = m_Acceleration * fTime + m_Speed;
	// Détermine la position : x(t) = 1/2*a*(t-to)² + v(t)*(t-to) + x0
	return m_Acceleration * 0.5 * SQR(fTime) + SpeedF * fTime + m_Position;
}

gtl::CVector3<float> CParticleElement::Speed () const
{
	// Détermine une durée c'est à dire la différence entre le temps initiale et le temps finale (t - to)
	float fTime = m_TimeMove.GetTime ();
	// Détermine la vitesse : v(t) = a(t)*(t-to) + v0
	return m_Acceleration * fTime + m_Speed;
}

// Pour affiner les effets de particules, plus le temps de vie d'une particule avance plus elle devient transparente, c'est à dire de moins en moins visible.
gtl::CColor4<float> CParticleElement::Color () const
{
	gtl::CColor4<float> Color = m_Color;
	Color (gtl::A) = 1 - (m_TimeLife.GetTime () / m_fTime);
	return Color;
}

bool CParticleElement::IsEnd () const
{
	return m_TimeLife.GetTime () > m_fTime;
}
