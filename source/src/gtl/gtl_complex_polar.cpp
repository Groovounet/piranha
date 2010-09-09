//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_complex_polar.cpp
//! \brief Classe CComplexPolar, pour l'utilisation de la forme polaire des nombres complexes.
//////////////////////////////////////////////////////////////////////////////

// r : Identify the float part of a complex number
// i : Identify the imaginary part of a complex number
// m : Identify the modulus of a complex number
// a : Identify the angle of a complex number
// c : Identify a complex

#include "gtl_complex_polar.h"
#include <cmath>

namespace gtl {

CComplexPolar::CComplexPolar ()
{
	m_fData[0] = 0;
	m_fData[1] = 0;
}

CComplexPolar::CComplexPolar (float m, float a)
{
	m_fData[0] = m;
	m_fData[1] = a;
}

CComplexPolar::CComplexPolar (float c[2])
{
	m_fData[0] = c[0];
	m_fData[1] = c[1];
}

CComplexPolar::CComplexPolar (const CComplexPolar & c)
{
	m_fData[0] = c.m_fData[0];
	m_fData[1] = c.m_fData[1];
}

CComplexPolar::CComplexPolar (const CComplexAlgebraic & c)
{
	m_fData[0] = sqrt (c.GetReal () * c.GetReal () + c.GetImaginary () * c.GetImaginary ());
	m_fData[1] = acos (c.GetReal () / c.Modulus ());
}

CComplexPolar::operator float* ()
{
	return m_fData;
}

CComplexPolar::operator const float* ()
{
	return m_fData;
}

CComplexPolar& CComplexPolar::operator= (const CComplexPolar & c)
{
	m_fData[0] = c.m_fData[0];
	m_fData[1] = c.m_fData[1]; 
	return *this;
}

CComplexPolar& CComplexPolar::operator= (const CComplexAlgebraic & c)
{
	return (*this = CComplexPolar (c));
}

CComplexPolar CComplexPolar::operator* (const CComplexPolar & c) const
{
	CComplexPolar Return;
	Return.m_fData[0] = m_fData[0] * c.m_fData[0];
	Return.m_fData[1] = fmod (m_fData[1] + c.m_fData[1], static_cast<float>(2.f * PI));
	return Return;
}

CComplexPolar& CComplexPolar::operator*= (const CComplexPolar & c)
{
	m_fData[0] = m_fData[0] * c.m_fData[0];
	m_fData[1] = fmod (m_fData[1] + c.m_fData[1], static_cast<float>(2.f * PI));
	return *this;
}

CComplexPolar CComplexPolar::operator/ (const CComplexPolar & c) const
{
	CComplexPolar Return;
	Return.m_fData[0] = m_fData[0] / c.m_fData[0];
	Return.m_fData[1] = fmod (m_fData[1] - c.m_fData[1], static_cast<float> (2.f * PI));
	return Return;
}

CComplexPolar& CComplexPolar::operator/= (const CComplexPolar & c)
{
	m_fData[0] = m_fData[0] / c.m_fData[0];
	m_fData[1] = fmod (m_fData[1] - c.m_fData[1], static_cast<float> (2.f * PI));
	return *this;
}

bool CComplexPolar::operator== (const CComplexPolar & c) const
{
	return (m_fData[0] == c.m_fData[0] && m_fData[1] == c.m_fData[1]);
}

bool CComplexPolar::operator!= (const CComplexPolar & c) const
{
	return !(*this==c);
}

float CComplexPolar::GetModulus () const
{
	return m_fData[0];
}

float CComplexPolar::GetAngle () const
{
	return m_fData[1];
}

void CComplexPolar::SetModulus (float m)
{
	m_fData[0] = m;
}

void CComplexPolar::SetAngle (float a)
{
	m_fData[1] = a;
}

float& CComplexPolar::Modulus ()
{
	return m_fData[0];
}

float& CComplexPolar::Angle ()
{
	return m_fData[1];
}

CComplexPolar& CComplexPolar::Inverse ()
{
	m_fData[0] = (m_fData[0] != 0) ? 1 / m_fData[0] : 0;
	m_fData[1] = -m_fData[1];
	return *this;
}

CComplexPolar CComplexPolar::GetInverse () const
{
	CComplexPolar Return;
	Return.m_fData[0] = (m_fData[0] != 0) ? 1 / m_fData[0] : 0;
	Return.m_fData[1] = -m_fData[1];
	return Return;
}
/*
CComplexPolar CComplexPolar::operator- ()
{
	return GetOpposite ();
}

CComplexPolar& CComplexPolar::Opposite ()
{
	return *this;
}

CComplexPolar CComplexPolar::GetOpposite () const
{
	CComplexPolar Return;
	return Return;
}
*/
CComplexPolar& CComplexPolar::Conjugate ()
{
	m_fData[1] = -m_fData[1];
	return *this;
}

CComplexPolar CComplexPolar::GetConjugate () const
{
	CComplexPolar Return;
	Return.m_fData[0] = m_fData[0];
	Return.m_fData[1] = -m_fData[1];
	return Return;
}

float CComplexPolar::Real () const
{
	return m_fData[0] * cos (m_fData[1]);
}

float CComplexPolar::Imaginary () const
{
	return m_fData[0] * sin (m_fData[1]);
}

}; // namespace gtl
