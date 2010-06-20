//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_complex_polar.h
//! \brief Classe CComplexPolar, pour l'utilisation de la forme polaire des nombres complexes.
//////////////////////////////////////////////////////////////////////////////

// r : Identify the float part of a complex number
// i : Identify the imaginary part of a complex number
// m : Identify the modulus of a complex number
// a : Identify the angle of a complex number
// c : Identify a complex

#ifndef __GTL_COMPLEX_POLAR_H__
#define __GTL_COMPLEX_POLAR_H__

#include "gtl_math.h"
#include "gtl_complex_algebraic.h"

namespace gtl {

class CComplexAlgebraic;

//! \brief Classe pour l'utilisation de la forme polaire des nombres complexes.
class CComplexPolar
{
private:
	float m_fData[2]; // z = m (cos (a) + i * sin (a)) => m = m_fData[0], a = m_fData[1]

public:
	CComplexPolar ();
	CComplexPolar (float r, float i);
	CComplexPolar (float c[2]);

	CComplexPolar (const CComplexPolar & c);
	CComplexPolar (const CComplexAlgebraic & c);

	operator float* ();
	operator const float* (); 

	CComplexPolar& operator= (const CComplexPolar & c);
	CComplexPolar& operator= (const CComplexAlgebraic & c);

	CComplexPolar operator* (const CComplexPolar & c) const;
	CComplexPolar& operator*= (const CComplexPolar & c);

	CComplexPolar operator/ (const CComplexPolar & c) const;
	CComplexPolar& operator/= (const CComplexPolar & c);

	bool operator== (const CComplexPolar & c) const;
	bool operator!= (const CComplexPolar & c) const;

	float GetModulus () const;
	float GetAngle () const;

	void SetModulus (float m);
	void SetAngle (float a);

	float& Modulus ();
	float& Angle ();

	CComplexPolar& Inverse ();
	CComplexPolar GetInverse () const;
/*
	CComplexPolar operator- ();
	CComplexPolar& Opposite ();
	CComplexPolar GetOpposite () const;
*/
	CComplexPolar& Conjugate ();
	CComplexPolar GetConjugate () const;

	float Real () const;
	float Imaginary () const;
};

}; // namespace gtl

#endif //__GTL_COMPLEX_POLAR_H__
