//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_matrix3x3.h
//! \brief Classe CMatrix3x3, représentant une matrice carré 3*3.
//////////////////////////////////////////////////////////////////////////////

// m : Name of the matrix variable (CMatrix3x3<T>)
// v : Name of the vector variable (CVector3<T>)
// a : Name of the array variable (T*)
// s : Name of the scalar variable (T)

#ifndef GTL_MATRIX_3X3_H
#define GTL_MATRIX_3X3_H

#include "gtl_vector2.h"
#include "gtl_vector3.h"

namespace gtl {

#define GTL_MATRIX_3X3_RANG 3

//! \brief Classe représentant une matrice carré 3*3.
template <typename T> class CMatrix3x3
{
private:
	// Member variable
	T m_Value[GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG];

public:
	// Constructor
	CMatrix3x3 () {Identity ();}

	CMatrix3x3 (const T _00, const T _10, const T _20,
		const T _01, const T _11, const T _21,
		const T _02, const T _12, const T _22)
	{
		m_Value[0] = _00; m_Value[1] = _10; m_Value[2] = _20;
		m_Value[3] = _01; m_Value[4] = _11; m_Value[5] = _21;
		m_Value[6] = _02; m_Value[7] = _12; m_Value[8] = _22;
	}

	CMatrix3x3 (const CMatrix3x3<T> & m)
	{
		for (unsigned char j=0; j<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); j++)
			m_Value[j] = m.m_Value[j];
	}

	CMatrix3x3 (const T a[GTL_MATRIX_3X3_RANG*GTL_MATRIX_3X3_RANG])
	{
		for (unsigned char i=0; i<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); i++)
			value[i] = a[i];
	}

	CMatrix3x3 (const T a1[GTL_MATRIX_3X3_RANG], const T a2[GTL_MATRIX_3X3_RANG], const T a3[GTL_MATRIX_3X3_RANG])
	{
		int i=0;
		for (i=0; i<(GTL_MATRIX_3X3_RANG * 1); i++)
			m_Value[i] = a1[i % GTL_MATRIX_3X3_RANG];
		for (i=3; i<(GTL_MATRIX_3X3_RANG * 2); i++)
			m_Value[i] = a2[i % GTL_MATRIX_3X3_RANG];
		for (i=6; i<(GTL_MATRIX_3X3_RANG * 3); i++)
			m_Value[i] = a3[i % GTL_MATRIX_3X3_RANG];
	}

	CMatrix3x3 (CVector3<T> v1, CVector3<T> v2, CVector3<T> v3)
	{
		m_Value[ 0] = v1 (X); m_Value[ 1] = v1 (Y); m_Value[ 2] = v1 (Z);
		m_Value[ 3] = v2 (X); m_Value[ 4] = v2 (Y); m_Value[ 5] = v2 (Z);
		m_Value[ 6] = v3 (X); m_Value[ 7] = v3 (Y); m_Value[ 8] = v3 (Z);
	}

	CMatrix3x3 (const CVector3<T> v[GTL_MATRIX_3X3_RANG])
	{
		for (unsigned char j=0; j<GTL_MATRIX_3X3_RANG; j++)
		{
			m_Value[j * GTL_MATRIX_3X3_RANG + 0] = v[j] (X);
			m_Value[j * GTL_MATRIX_3X3_RANG + 1] = v[j] (Y);
			m_Value[j * GTL_MATRIX_3X3_RANG + 2] = v[j] (Z);
		}
	}

	inline CMatrix3x3<T>& operator= (const CMatrix3x3<T>& m)
	{
		for (unsigned char j=0; j<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); j++)
			m_Value[j] = m.m_Value[j];
		return *this;
	}

	inline T& operator() (const TCoord & l, const TCoord & c)
	{
		if ((l > 2) || (c > 2))
			return m_Value[0];
		return m_Value[c * GTL_MATRIX_3X3_RANG + l];
	}

	inline operator T* ()
	{
		return m_Value;
	}

	inline operator const T* ()
	{
		return m_Value;
	}

	// Comparison operators
	bool operator== (const CMatrix3x3<T> & m) const
	{
		for (unsigned char j=0; j<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); j++)
			if (m_Value[j] != m.m_Value[j])
				return false;
		return true;
	}

	bool operator!= (const CMatrix3x3<T> & m) const
	{
		for (unsigned char j=0; j<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); j++)
			if (m_Value[j] != m.m_Value[j])
				return true;
		return false;
	}

	CMatrix3x3 operator+ (const CMatrix3x3<T> & m) const
	{
		return CMatrix3x3<T> (
			m_Value[ 0]+m.m_Value[ 0], m_Value[ 1]+m.m_Value[ 1], m_Value[ 2]+m.m_Value[ 2], 
			m_Value[ 3]+m.m_Value[ 3], m_Value[ 4]+m.m_Value[ 4], m_Value[ 5]+m.m_Value[ 5],
			m_Value[ 6]+m.m_Value[ 6], m_Value[ 7]+m.m_Value[ 7], m_Value[ 8]+m.m_Value[ 8]
		);
	}

	CMatrix3x3 operator+= (const CMatrix3x3<T> & m)
	{
		for (unsigned char j=0; j<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); j++)
			m_Value[j] += m.m_Value[j];
		return *this;
	}
		
	CMatrix3x3 operator- (const CMatrix3x3<T> & m) const
	{
		return CMatrix3x3<T> (
			m_Value[ 0]-m.m_Value[ 0], m_Value[ 1]-m.m_Value[ 1], m_Value[ 2]-m.m_Value[ 2], 
			m_Value[ 3]-m.m_Value[ 3], m_Value[ 4]-m.m_Value[ 4], m_Value[ 5]-m.m_Value[ 5],
			m_Value[ 6]-m.m_Value[ 6], m_Value[ 7]-m.m_Value[ 7], m_Value[ 8]-m.m_Value[ 8]
		);
	}

	CMatrix3x3 operator-= (const CMatrix3x3<T> & m)
	{
		for (unsigned char j=0; j<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); j++)
			m_Value[j] -= m.m_Value[j];
		return *this;
	}

	CMatrix3x3 operator* (const T s) const
	{
		CMatrix3x3 m (*this);
		for (unsigned char i=0; i<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); i++)
			m.m_Value[i] *= s;
		return m;
	}

	CMatrix3x3 operator*= (const T s)
	{
		for (unsigned char i=0; i<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); i++)
			m_Value[i] *= s;
		return *this;
	}

	CVector3<T> operator* (CVector3<T> & v) const
	{
		CVector3<T> Vector;

		Vector (X) = v(X) * m_Value[0] + v(Y) * m_Value[1] + v(Z) * m_Value[2];
		Vector (Y) = v(X) * m_Value[3] + v(Y) * m_Value[4] + v(Z) * m_Value[5];
		Vector (Z) = v(X) * m_Value[6] + v(Y) * m_Value[7] + v(Z) * m_Value[8];

		return Vector;
	}

	CMatrix3x3 operator* (const CMatrix3x3 & m) const
	{
		CMatrix3x3<T> Matrix;

		Matrix.m_Value[0] = m_Value[0]*m.m_Value[0] + m_Value[1]*m.m_Value[3] + m_Value[2]*m.m_Value[6];
		Matrix.m_Value[1] = m_Value[0]*m.m_Value[1] + m_Value[1]*m.m_Value[4] + m_Value[2]*m.m_Value[7];
		Matrix.m_Value[2] = m_Value[0]*m.m_Value[2] + m_Value[1]*m.m_Value[5] + m_Value[2]*m.m_Value[8];

		Matrix.m_Value[3] = m_Value[3]*m.m_Value[0] + m_Value[4]*m.m_Value[3] + m_Value[5]*m.m_Value[6];
		Matrix.m_Value[4] = m_Value[3]*m.m_Value[1] + m_Value[4]*m.m_Value[4] + m_Value[5]*m.m_Value[7];
		Matrix.m_Value[5] = m_Value[3]*m.m_Value[2] + m_Value[4]*m.m_Value[5] + m_Value[5]*m.m_Value[8];

		Matrix.m_Value[6] = m_Value[6]*m.m_Value[0] + m_Value[7]*m.m_Value[3] + m_Value[8]*m.m_Value[6];
		Matrix.m_Value[7] = m_Value[6]*m.m_Value[1] + m_Value[7]*m.m_Value[4] + m_Value[8]*m.m_Value[7];
		Matrix.m_Value[8] = m_Value[6]*m.m_Value[2] + m_Value[7]*m.m_Value[5] + m_Value[8]*m.m_Value[8];

		return Matrix;
	}

	CMatrix3x3 operator*= (const CMatrix3x3 & m)
	{
		return (*this = *this * m);
	}

	CMatrix3x3 operator/ (const T s) const
	{
		CMatrix3x3 m (*this);
		for (unsigned char i=0; i<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); i++)
			m.m_Value[i] /= s;
		return m;
	}

	CMatrix3x3 operator/= (const T s)
	{
		for (unsigned char i=0; i<(GTL_MATRIX_3X3_RANG * GTL_MATRIX_3X3_RANG); i++)
			m_Value[i] /= s;
		return *this;
	}

	CMatrix3x3 operator/ (const CMatrix3x3 & m) const
	{
		return *this * m.GetInvert ();
	}

	CMatrix3x3 operator/= (const CMatrix3x3 & m)
	{
		return (*this = *this * m.GetInvert ());
	}

	CMatrix3x3 operator- () const
	{
		CMatrix3x3<T> Matrix;
		for (unsigned char j=0; j<GTL_MATRIX_3X3_RANG; j++)
			Matrix[j] = -value[j];
		return Matrix;
	}

	CMatrix3x3 GetIdentity ()
	{
		CMatrix3x3<T> Matrix;
		return Matrix.Identity ();
	}

	void Identity ()
	{
		m_Value[0] = static_cast<T> (1); m_Value[1] = static_cast<T> (0); m_Value[2] = static_cast<T> (0);
		m_Value[3] = static_cast<T> (0); m_Value[4] = static_cast<T> (1); m_Value[5] = static_cast<T> (0);
		m_Value[6] = static_cast<T> (0); m_Value[7] = static_cast<T> (0); m_Value[8] = static_cast<T> (1);
	}

	CMatrix3x3 GetInvert ()
	{
		CMatrix3x3<T> Matrix (
			m_Value[4] * m_Value[8] - m_Value[5] * m_Value[7], m_Value[2] * m_Value[7] - m_Value[1] * m_Value[8], m_Value[1] * m_Value[5] - m_Value[2] * m_Value[4],
			m_Value[5] * m_Value[6] - m_Value[3] * m_Value[8], m_Value[0] * m_Value[8] - m_Value[2] * m_Value[6], m_Value[2] * m_Value[3] - m_Value[0] * m_Value[5],
			m_Value[3] * m_Value[7] - m_Value[4] * m_Value[6], m_Value[1] * m_Value[6] - m_Value[0] * m_Value[7], m_Value[0] * m_Value[4] - m_Value[1] * m_Value[3]);
		return Matrix * 1 / Det ();
	}

	CMatrix3x3 Invert ()
	{
		return *this = GetInvert ();
	}

	T Det ()
	{
		return m_Value[0] * (m_Value[4] * m_Value[8] - m_Value[5] * m_Value[7]) \
             - m_Value[1] * (m_Value[3] * m_Value[8] - m_Value[5] * m_Value[6]) \
             + m_Value[2] * (m_Value[3] * m_Value[7] - m_Value[4] * m_Value[6]);
	}
};

}; // namespace gtl

#endif //GTL_MATRIX_3X3_H
