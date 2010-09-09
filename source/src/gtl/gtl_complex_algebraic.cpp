//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_complex_algebraic.cpp
//! \brief Classe CComplexAlgebraic, pour l'utilisation de la forme algebrique des nombres complexes.
//////////////////////////////////////////////////////////////////////////////

// r : Identify the float part of a complex number
// i : Identify the imaginary part of a complex number
// m : Identify the modulus of a complex number
// a : Identify the angle of a complex number
// c : Identify a complex

#include "gtl_complex_algebraic.h"
#include <cmath>

namespace gtl {

CComplexAlgebraic::CComplexAlgebraic ()
{
	m_fData[0] = 0;
	m_fData[1] = 0;
}

CComplexAlgebraic::CComplexAlgebraic (float r, float i)
{
	m_fData[0] = r;
	m_fData[1] = i;
}

CComplexAlgebraic::CComplexAlgebraic (float c[2])
{
	m_fData[0] = c[0];
	m_fData[1] = c[1];
}

CComplexAlgebraic::CComplexAlgebraic (const CComplexAlgebraic & c)
{
	m_fData[0] = c.m_fData[0];
	m_fData[1] = c.m_fData[1];
}

CComplexAlgebraic::CComplexAlgebraic (const CComplexPolar & c)
{
	m_fData[0] = c.GetModulus () * static_cast<float> (cos (c.GetAngle ()));
	m_fData[1] = c.GetModulus () * static_cast<float> (sin (c.GetAngle ()));
}

CComplexAlgebraic::operator float* ()
{
	return m_fData;
}

CComplexAlgebraic::operator const float* ()
{
	return m_fData;
}

CComplexAlgebraic& CComplexAlgebraic::operator= (const CComplexAlgebraic & c)
{
	m_fData[0] = c.m_fData[0];
	m_fData[1] = c.m_fData[1]; 
	return *this;
}

CComplexAlgebraic& CComplexAlgebraic::operator= (const CComplexPolar & c)
{
	return (*this = CComplexAlgebraic (c));
}

CComplexAlgebraic CComplexAlgebraic::operator+ (const CComplexAlgebraic & c) const
{
	CComplexAlgebraic Return;
	Return.m_fData[0] = m_fData[0] + c.m_fData[0];
	Return.m_fData[1] = m_fData[1] + c.m_fData[1];
	return Return;
}

CComplexAlgebraic& CComplexAlgebraic::operator+= (const CComplexAlgebraic & c)
{
	m_fData[0] += c.m_fData[0];
	m_fData[1] += c.m_fData[1];
	return *this;
}

CComplexAlgebraic CComplexAlgebraic::operator- (const CComplexAlgebraic & c) const
{
	CComplexAlgebraic Return;
	Return.m_fData[0] = m_fData[0] - c.m_fData[0];
	Return.m_fData[1] = m_fData[1] - c.m_fData[1];
	return Return;
}

CComplexAlgebraic& CComplexAlgebraic::operator-= (const CComplexAlgebraic & c)
{
	m_fData[0] -= c.m_fData[0];
	m_fData[1] -= c.m_fData[1];
	return *this;
}

CComplexAlgebraic CComplexAlgebraic::operator* (const CComplexAlgebraic & c) const
{
	CComplexAlgebraic Return;
	Return.m_fData[0] = m_fData[0] * c.m_fData[0] - m_fData[1] * c.m_fData[1];
	Return.m_fData[1] = m_fData[0] * c.m_fData[1] + m_fData[1] * c.m_fData[0];
	return Return;
}

CComplexAlgebraic& CComplexAlgebraic::operator*= (const CComplexAlgebraic & c)
{
	CComplexAlgebraic Temp;
	Temp.m_fData[0] = m_fData[0] * c.m_fData[0] - m_fData[1] * c.m_fData[1];
	Temp.m_fData[1] = m_fData[0] * c.m_fData[1] + m_fData[1] * c.m_fData[0];
	return (*this = Temp);
}

CComplexAlgebraic CComplexAlgebraic::operator/ (const CComplexAlgebraic & c) const
{
	return *this * c.GetInverse ();
}

CComplexAlgebraic& CComplexAlgebraic::operator/= (const CComplexAlgebraic & c)
{
	return *this = *this * c.GetInverse ();
}

bool CComplexAlgebraic::operator== (const CComplexAlgebraic & c) const
{
	return (m_fData[0] == c.m_fData[0] && m_fData[1] == c.m_fData[1]);
}

bool CComplexAlgebraic::operator!= (const CComplexAlgebraic & c) const
{
	return !(*this==c);
}

float CComplexAlgebraic::GetReal () const
{
	return m_fData[0];
}

float CComplexAlgebraic::GetImaginary () const
{
	return m_fData[1];
}

void CComplexAlgebraic::SetReal (float r)
{
	m_fData[0] = r;
}

void CComplexAlgebraic::SetImaginary (float i)
{
	m_fData[1] = i;
}

float& CComplexAlgebraic::Real ()
{
	return m_fData[0];
}

float& CComplexAlgebraic::Imaginary ()
{
	return m_fData[1];
}

CComplexAlgebraic& CComplexAlgebraic::Inverse ()
{
	float fDenominator = sqrt (m_fData[0]) + sqrt (m_fData[1]);
	m_fData[0] = m_fData[0] / fDenominator;
	m_fData[1] = m_fData[1] / fDenominator;
	return *this;
}

CComplexAlgebraic CComplexAlgebraic::GetInverse () const
{
	CComplexAlgebraic Return;
	float fDenominator = sqrt (m_fData[0]) + sqrt (m_fData[1]);
	Return.m_fData[0] = m_fData[0] / fDenominator;
	Return.m_fData[1] = m_fData[1] / fDenominator;
	return Return;
}

CComplexAlgebraic CComplexAlgebraic::operator- ()
{
	return GetOpposite ();
}

CComplexAlgebraic& CComplexAlgebraic::Opposite ()
{
	m_fData[0] = -m_fData[0];
	m_fData[1] = -m_fData[1];
	return *this;
}

CComplexAlgebraic CComplexAlgebraic::GetOpposite () const
{
	CComplexAlgebraic Return;
	Return.m_fData[0] = -m_fData[0];
	Return.m_fData[1] = -m_fData[1];
	return Return;
}

CComplexAlgebraic& CComplexAlgebraic::Conjugate ()
{
	m_fData[1] = -m_fData[1];
	return *this;
}

CComplexAlgebraic CComplexAlgebraic::GetConjugate () const
{
	CComplexAlgebraic Return;
	Return.m_fData[0] = m_fData[0];
	Return.m_fData[1] = -m_fData[1];
	return Return;
}

float CComplexAlgebraic::Modulus () const
{
	return sqrt (m_fData[0] * m_fData[0] + m_fData[1] * m_fData[1]);
}

float CComplexAlgebraic::Angle () const
{
	float m = Modulus();
	return (m != 0 ? (acos (m_fData[0] / m)) : 0);
}

}; // namespace gtl
