//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_complex_algebraic.h
//! \brief Classe CComplexAlgebraic, pour l'utilisation de la forme algebrique des nombres complexes.
//////////////////////////////////////////////////////////////////////////////

// r : Identify the real part of a complex number
// i : Identify the imaginary part of a complex number
// m : Identify the modulus of a complex number
// a : Identify the angle of a complex number
// c : Identify a complex

#ifndef __GTL_COMPLEX_ALGEBRAIE_H__
#define __GTL_COMPLEX_ALGEBRAIE_H__

#include "gtl_math.h"
#include "gtl_complex_polar.h"

namespace gtl {

class CComplexPolar;

//! \brief Classe pour l'utilisation de la forme algebrique des nombres complexes.
class CComplexAlgebraic
{
private:
	float m_fData[2]; // z = a + b * i => a = m_fData[0], b = m_fData[1]

public:
	CComplexAlgebraic ();

	CComplexAlgebraic (float r, float i);
	CComplexAlgebraic (float c[2]);

	CComplexAlgebraic (const CComplexAlgebraic & c);
	CComplexAlgebraic (const CComplexPolar & c);

	operator float* ();
	operator const float* (); 

	CComplexAlgebraic& operator= (const CComplexAlgebraic & c);
	CComplexAlgebraic& operator= (const CComplexPolar & c);

	CComplexAlgebraic operator+ (const CComplexAlgebraic & c) const;
	CComplexAlgebraic& operator+= (const CComplexAlgebraic & c);

	CComplexAlgebraic operator- (const CComplexAlgebraic & c) const;
	CComplexAlgebraic& operator-= (const CComplexAlgebraic & c);

	CComplexAlgebraic operator* (const CComplexAlgebraic & c) const;
	CComplexAlgebraic& operator*= (const CComplexAlgebraic & c);

	CComplexAlgebraic operator/ (const CComplexAlgebraic & c) const;
	CComplexAlgebraic& operator/= (const CComplexAlgebraic & c);

	bool operator== (const CComplexAlgebraic & c) const;
	bool operator!= (const CComplexAlgebraic & c) const;

	float GetReal () const;
	float GetImaginary () const;

	void SetReal (float r);
	void SetImaginary (float i);

	float& Real ();
	float& Imaginary ();

	CComplexAlgebraic& Inverse ();
	CComplexAlgebraic GetInverse () const;

	CComplexAlgebraic operator- ();
	CComplexAlgebraic& Opposite ();
	CComplexAlgebraic GetOpposite () const;

	CComplexAlgebraic& Conjugate ();
	CComplexAlgebraic GetConjugate () const;

	float Modulus () const;
	float Angle () const;
};

}; // namespace gtl

#endif //__GTL_COMPLEX_ALGEBRAIE_H__
