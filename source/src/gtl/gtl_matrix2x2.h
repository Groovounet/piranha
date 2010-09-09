//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_matrix2x2.h
//! \brief Classe CMatrix2x2, représentant une matrice carré 2*2.
//////////////////////////////////////////////////////////////////////////////

// m : Name of the matrix variable (CMatrix2x2<T>)
// v : Name of the vector variable (CVector2<T>)
// a : Name of the array variable (T*)
// s : Name of the scalar variable (T)

#ifndef GTL_MATRIX_2X2_H
#define GTL_MATRIX_2X2_H

#include "gtl_vector2.h"

namespace gtl {

#define GTL_MATRIX_2X2_RANG 2

//! \brief Classe représentant une matrice carré 2*2.
template <typename T> class CMatrix2x2
{
private:
	// Member variable
	T m_Value[GTL_MATRIX_2X2_RANG * GTL_MATRIX_2X2_RANG];

public:
	// Constructor
	CMatrix2x2 () {Identity ();}

	CMatrix2x2 (const T _00, const T _01, 
		const T _10, const T _11)
	{
		value[0][0] = _00; value[0][1] = _01;
		value[1][0] = _10; value[1][1] = _11;
	}

	CMatrix2x2 (const CMatrix2x2<T> & m)
	{
		for (unsigned char j=0; j<(GTL_MATRIX_2X2_RANG * GTL_MATRIX_2X2_RANG); j++)
			m_Value[j] = m.m_Value[j];
	}

	CMatrix2x2 (const T a[GTL_MATRIX_2X2_RANG*GTL_MATRIX_2X2_RANG])
	{
		for (unsigned char i=0; i<(GTL_MATRIX_2X2_RANG * GTL_MATRIX_2X2_RANG); i++)
			value[i] = a[i];
	}

	CMatrix2x2 (const T a1[GTL_MATRIX_2X2_RANG], const T a2[GTL_MATRIX_2X2_RANG])
	{
		int i=0;
		for (i=0; i<(GTL_MATRIX_2X2_RANG * 1); i++)
			m_Value[i] = a1[i % GTL_MATRIX_2X2_RANG];
		for (i=2; i<(GTL_MATRIX_2X2_RANG * 2); i++)
			m_Value[i] = a2[i % GTL_MATRIX_2X2_RANG];
	}

	CMatrix2x2 (CVector2<T> v1, CVector2<T> v2)
	{
		m_Value[ 0] = v1 (X); m_Value[ 1] = v1 (Y);
		m_Value[ 2] = v2 (X); m_Value[ 3] = v2 (Y);
	}

	CMatrix2x2 (const CVector2<T> v[GTL_MATRIX_2X2_RANG])
	{
		for (unsigned char j=0; j<GTL_MATRIX_2X2_RANG; j++)
		{
			m_Value[j * GTL_MATRIX_2X2_RANG + 0] = v[j] (X);
			m_Value[j * GTL_MATRIX_2X2_RANG + 1] = v[j] (Y);
		}
	}

	inline CMatrix2x2<T>& operator= (const CMatrix2x2<T>& m)
	{
		for (unsigned char j=0; j<(GTL_MATRIX_2X2_RANG * GTL_MATRIX_2X2_RANG); j++)
			m_Value[j] = m.m_Value[j];
		return *this;
	}

	inline T& operator() (const TCoord & l, const TCoord & c)
	{
		if ((l > 1) || (c > 1))
			return m_Value[0];
		return m_Value[c * GTL_MATRIX_2X2_RANG + l];
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
	bool operator== (const CMatrix2x2<T> & m) const
	{
		for (unsigned char j=0; j<(GTL_MATRIX_2X2_RANG * GTL_MATRIX_2X2_RANG); j++)
			if (value[j] != m.value[j])
				return false;
		return true;
	}

	bool operator!= (const CMatrix2x2<T> & m) const
	{
		for (unsigned char j=0; j<(GTL_MATRIX_2X2_RANG * GTL_MATRIX_2X2_RANG); j++)
			if (value[j] != m.value[j])
				return true;
		return false;
	}

	CMatrix2x2 operator+ (const CMatrix2x2<T> & m) const
	{
		return CMatrix2x2<T> (
			m_Value[ 0]+m.m_Value[ 0], m_Value[ 1]+m.m_Value[ 1],
			m_Value[ 2]+m.m_Value[ 2], m_Value[ 3]+m.m_Value[ 3]
		);
	}

	CMatrix2x2 operator+= (const CMatrix2x2<T> & m)
	{
		for (unsigned char j=0; j<(GTL_MATRIX_2X2_RANG*GTL_MATRIX_2X2_RANG); j++)
			m_Value[j] += m.m_Value[j];
		return *this;
	}
		
	CMatrix2x2 operator- (const CMatrix2x2<T> & m) const
	{
		return CMatrix2x2<T> (
			m_Value[ 0]-m.m_Value[ 0], m_Value[ 1]-m.m_Value[ 1],
			m_Value[ 2]-m.m_Value[ 2], m_Value[ 3]-m.m_Value[ 3]
		);
	}

	CMatrix2x2 operator-= (const CMatrix2x2<T> & m)
	{
		for (unsigned char j=0; j<(GTL_MATRIX_2X2_RANG*GTL_MATRIX_2X2_RANG); j++)
			m_Value[j] -= m.m_Value[j];
		return *this;
	}

	CMatrix2x2 operator* (const T s) const
	{
		CMatrix2x2 m (*this);
		for (unsigned char i=0; i<(GTL_MATRIX_2X2_RANG * GTL_MATRIX_2X2_RANG); i++)
			m.m_Value[i] *= s;
		return m;
	}

	CMatrix2x2 operator*= (const T s)
	{
		for (unsigned char i=0; i<(GTL_MATRIX_2X2_RANG * GTL_MATRIX_2X2_RANG); i++)
			m_Value[i] *= s;
		return *this;
	}

	CVector2<T> operator* (CVector2<T> & v) const
	{
		CVector2<T> Vector;

		Vector (X) = v(X) * m_Value[0] + v(Y) * m_Value[1];
		Vector (Y) = v(X) * m_Value[2] + v(Y) * m_Value[3];

		return Vector;
	}


	CMatrix2x2 operator* (const CMatrix2x2 & m) const
	{
		CMatrix2x2<T> Matrix;

		Matrix.m_Value[0] = m_Value[0]*m.m_Value[0] + m_Value[1]*m.m_Value[2];
		Matrix.m_Value[1] = m_Value[0]*m.m_Value[1] + m_Value[1]*m.m_Value[3];

		Matrix.m_Value[2] = m_Value[2]*m.m_Value[0] + m_Value[3]*m.m_Value[2];
		Matrix.m_Value[3] = m_Value[2]*m.m_Value[1] + m_Value[3]*m.m_Value[3];

		return Matrix;
	}

	CMatrix2x2 operator*= (const CMatrix2x2 & m)
	{
		return (*this = *this * m);
	}

	CMatrix2x2 operator/ (const T s) const
	{
		CMatrix2x2 m (*this);
		for (unsigned char i=0; i<(GTL_MATRIX_2X2_RANG * GTL_MATRIX_2X2_RANG); i++)
			m.m_Value[i] /= s;
		return m;
	}

	CMatrix2x2 operator/= (const T s)
	{
		for (unsigned char i=0; i<(GTL_MATRIX_2X2_RANG * GTL_MATRIX_2X2_RANG); i++)
			m_Value[i] /= s;
		return *this;
	}

	CMatrix2x2 operator/ (const CMatrix2x2 & m) const
	{
		return *this * m.GetInvert ();
	}

	CMatrix2x2 operator/= (const CMatrix2x2 & m)
	{
		return (*this = *this * m.GetInvert ());
	}

	CMatrix2x2 operator- () const
	{
		CMatrix2x2<T> Matrix;
		for (unsigned char j=0; j<GTL_MATRIX_2X2_RANG; j++)
			Matrix[j] = -value[j];
		return Matrix;
	}

	CMatrix2x2 GetIdentity ()
	{
		return CMatrix2x2<T> (1, 0, 0, 1);
	}

	void Identity ()
	{
		m_Value[0] = m_Value[3] = static_cast<T> (1);
		m_Value[1] = m_Value[2] = static_cast<T> (0);
	}

	CMatrix2x2 GetInvert ()
	{
		CMatrix2x2<T> Matrix (m_Value[3], -m_Value[1], -m_Value[2], m_Value[0]);
		return 1 / Det () * Matrix;
	}

	void Invert ()
	{
		*this = GetInvert ();
	}

	T Det ()
	{
		return m_Value[0] * m_Value[3] - m_Value[1] * m_Value[2];
	}
};

}; // namespace gtl

#endif //GTL_MATRIX_2X2_H

