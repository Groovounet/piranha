//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_matrix4x4.h
//! \brief Classe CMatrix4x4, représentant une matrice carré 4*4.
//////////////////////////////////////////////////////////////////////////////

// m : Name of the matrix variable (CMatrix4x4<T>)
// v : Name of the vector variable (CVector4<T>)
// a : Name of the array variable (T*)
// s : Name of the scalar variable (T)

#ifndef GTL_MATRIX_4X4_H
#define GTL_MATRIX_4X4_H

#include "gtl_vector3.h"
#include "gtl_vector4.h"

namespace gtl {

#define GTL_MATRIX_4X4_RANG 4

//! \brief Classe représentant une matrice carré 4*4.
template <typename T> class CMatrix4x4
{
private:
	T m_Value[GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG];

public:
	// Constructor
	CMatrix4x4 () {Identity ();}

	CMatrix4x4 (const T s00, const T s01, const T s02, const T s03,
		const T s04, const T s05, const T s06, const T s07,
		const T s08, const T s09, const T s10, const T s11,
		const T s12, const T s13, const T s14, const T s15)
	{
		m_Value[ 0] = s00; m_Value[ 1] = s01; m_Value[ 2] = s02; m_Value[ 3] = s03;
		m_Value[ 4] = s04; m_Value[ 5] = s05; m_Value[ 6] = s06; m_Value[ 7] = s07;
		m_Value[ 8] = s08; m_Value[ 9] = s09; m_Value[10] = s10; m_Value[11] = s11;
		m_Value[12] = s12; m_Value[13] = s13; m_Value[14] = s14; m_Value[15] = s15;
	}

	CMatrix4x4 (const CMatrix4x4<T> & m)
	{
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			m_Value[i] = m.m_Value[i];
	}

	CMatrix4x4 (const T a[GTL_MATRIX_4X4_RANG*GTL_MATRIX_4X4_RANG])
	{
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			m_Value[i] = a[i];
	}

	CMatrix4x4 (const T a1[GTL_MATRIX_4X4_RANG], const T a2[GTL_MATRIX_4X4_RANG], const T a3[GTL_MATRIX_4X4_RANG], const T a4[GTL_MATRIX_4X4_RANG])
	{
		int i=0;
		for (i=0; i<(GTL_MATRIX_4X4_RANG * 1); i++)
			m_Value[i] = a1[i % GTL_MATRIX_4X4_RANG];
		for (i=4; i<(GTL_MATRIX_4X4_RANG * 2); i++)
			m_Value[i] = a2[i % GTL_MATRIX_4X4_RANG];
		for (i=8; i<(GTL_MATRIX_4X4_RANG * 3); i++)
			m_Value[i] = a3[i % GTL_MATRIX_4X4_RANG];
		for (i=12; i<(GTL_MATRIX_4X4_RANG * 4); i++)
			m_Value[i] = a4[i % GTL_MATRIX_4X4_RANG];
	}

	CMatrix4x4 (CVector4<T> v1, CVector4<T> v2, CVector4<T> v3, CVector4<T> v4)
	{
		m_Value[ 0] = v1 (X); m_Value[ 1] = v1 (Y); m_Value[ 2] = v1 (Z); m_Value[ 3] = v1 (W);
		m_Value[ 4] = v2 (X); m_Value[ 5] = v2 (Y); m_Value[ 6] = v2 (Z); m_Value[ 7] = v2 (W);
		m_Value[ 8] = v3 (X); m_Value[ 9] = v3 (Y); m_Value[10] = v3 (Z); m_Value[11] = v3 (W);
		m_Value[12] = v4 (X); m_Value[13] = v4 (Y); m_Value[14] = v4 (Z); m_Value[15] = v4 (W);
	}

	CMatrix4x4 (const CVector4<T> v[GTL_MATRIX_4X4_RANG])
	{
		for (unsigned char j=0; j<GTL_MATRIX_4X4_RANG; j++)
		{
			m_Value[j * GTL_MATRIX_4X4_RANG + 0] = v[j] (X);
			m_Value[j * GTL_MATRIX_4X4_RANG + 1] = v[j] (Y);
			m_Value[j * GTL_MATRIX_4X4_RANG + 2] = v[j] (Z);
			m_Value[j * GTL_MATRIX_4X4_RANG + 3] = v[j] (W);
		}
	}

	inline CMatrix4x4<T>& operator= (const CMatrix4x4<T>& m)
	{
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			m_Value[i] = m.m_Value[i];
		return *this;
	}

	inline T& operator() (const TCoord & l, const TCoord & c)
	{
		if ((l > 3) || (c > 3))
			return m_Value[0];
		return m_Value[c * GTL_MATRIX_4X4_RANG + l];
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
	bool operator== (const CMatrix4x4 & m) const
	{
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			if (m_Value[i] != m.m_Value[i])
				return false;
		return true;
	}

	bool operator!= (const CMatrix4x4 & m) const
	{
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			if (m_Value[i] != m.m_Value[i])
				return true;
		return false;
	}

	CMatrix4x4 operator+ (const CMatrix4x4 & m) const
	{
		return CMatrix4x4<T> (
			m_Value[ 0]+m.m_Value[ 0], m_Value[ 1]+m.m_Value[ 1], m_Value[ 2]+m.m_Value[ 2], m_Value[ 3]+m.m_Value[ 3],
			m_Value[ 4]+m.m_Value[ 4], m_Value[ 5]+m.m_Value[ 5], m_Value[ 6]+m.m_Value[ 6], m_Value[ 7]+m.m_Value[ 7],
			m_Value[ 8]+m.m_Value[ 8], m_Value[ 9]+m.m_Value[ 9], m_Value[10]+m.m_Value[10], m_Value[11]+m.m_Value[11],
			m_Value[12]+m.m_Value[12], m_Value[13]+m.m_Value[13], m_Value[14]+m.m_Value[14], m_Value[15]+m.m_Value[15]
		);
	}

	CMatrix4x4 operator+= (const CMatrix4x4 & m)
	{
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			m_Value[i] += m.m_Value[i];
		return *this;
	}
		
	CMatrix4x4 operator- (const CMatrix4x4 & m) const
	{
		return CMatrix4x4<T> (
			m_Value[ 0]-m.m_Value[ 0], m_Value[ 1]-m.m_Value[ 1], m_Value[ 2]-m.m_Value[ 2], m_Value[ 3]-m.m_Value[ 3],
			m_Value[ 4]-m.m_Value[ 4], m_Value[ 5]-m.m_Value[ 5], m_Value[ 6]-m.m_Value[ 6], m_Value[ 7]-m.m_Value[ 7],
			m_Value[ 8]-m.m_Value[ 8], m_Value[ 9]-m.m_Value[ 9], m_Value[10]-m.m_Value[10], m_Value[11]-m.m_Value[11],
			m_Value[12]-m.m_Value[12], m_Value[13]-m.m_Value[13], m_Value[14]-m.m_Value[14], m_Value[15]-m.m_Value[15]
		);
	}

	CMatrix4x4 operator-= (const CMatrix4x4 & m)
	{
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			m_Value[i] -= m.m_Value[i];
		return *this;
	}

	CMatrix4x4 operator* (const T s) const
	{
		CMatrix4x4 m (*this);
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			m.m_Value[i] *= s;
		return m;
	}

	CMatrix4x4 operator*= (const T s)
	{
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			m_Value[i] *= s;
		return *this;
	}

	CVector4<T> operator* (CVector4<T> & v) const
	{
		CVector4<T> Vector;

		Vector (X) = v(X) * m_Value[ 0] + v(Y) * m_Value[ 1] + v(Z) * m_Value[ 2] + v(W) * m_Value[ 3];
		Vector (Y) = v(X) * m_Value[ 4] + v(Y) * m_Value[ 5] + v(Z) * m_Value[ 6] + v(W) * m_Value[ 7];
		Vector (Z) = v(X) * m_Value[ 8] + v(Y) * m_Value[ 9] + v(Z) * m_Value[10] + v(W) * m_Value[11];
		Vector (W) = v(X) * m_Value[12] + v(Y) * m_Value[13] + v(Z) * m_Value[14] + v(W) * m_Value[15];

		return Vector;
	}

	CMatrix4x4 operator* (const CMatrix4x4 & m) const
	{
		CMatrix4x4<T> Matrix;

		Matrix.m_Value[ 0] = m_Value[ 0]*m.m_Value[ 0] + m_Value[ 1]*m.m_Value[ 4] + m_Value[ 2]*m.m_Value[ 8] + m_Value[ 3]*m.m_Value[12];
		Matrix.m_Value[ 1] = m_Value[ 0]*m.m_Value[ 1] + m_Value[ 1]*m.m_Value[ 5] + m_Value[ 2]*m.m_Value[ 9] + m_Value[ 3]*m.m_Value[13];
		Matrix.m_Value[ 2] = m_Value[ 0]*m.m_Value[ 2] + m_Value[ 1]*m.m_Value[ 6] + m_Value[ 2]*m.m_Value[10] + m_Value[ 3]*m.m_Value[14];
		Matrix.m_Value[ 3] = m_Value[ 0]*m.m_Value[ 3] + m_Value[ 1]*m.m_Value[ 7] + m_Value[ 2]*m.m_Value[11] + m_Value[ 3]*m.m_Value[15];

		Matrix.m_Value[ 4] = m_Value[ 4]*m.m_Value[ 0] + m_Value[ 5]*m.m_Value[ 4] + m_Value[ 6]*m.m_Value[ 8] + m_Value[ 7]*m.m_Value[12];
		Matrix.m_Value[ 5] = m_Value[ 4]*m.m_Value[ 1] + m_Value[ 5]*m.m_Value[ 5] + m_Value[ 6]*m.m_Value[ 9] + m_Value[ 7]*m.m_Value[13];
		Matrix.m_Value[ 6] = m_Value[ 4]*m.m_Value[ 2] + m_Value[ 5]*m.m_Value[ 6] + m_Value[ 6]*m.m_Value[10] + m_Value[ 7]*m.m_Value[14];
		Matrix.m_Value[ 7] = m_Value[ 4]*m.m_Value[ 3] + m_Value[ 5]*m.m_Value[ 7] + m_Value[ 6]*m.m_Value[11] + m_Value[ 7]*m.m_Value[15];

		Matrix.m_Value[ 8] = m_Value[ 8]*m.m_Value[ 0] + m_Value[ 9]*m.m_Value[ 4] + m_Value[10]*m.m_Value[ 8] + m_Value[11]*m.m_Value[12];
		Matrix.m_Value[ 9] = m_Value[ 8]*m.m_Value[ 1] + m_Value[ 9]*m.m_Value[ 5] + m_Value[10]*m.m_Value[ 9] + m_Value[11]*m.m_Value[13];
		Matrix.m_Value[10] = m_Value[ 8]*m.m_Value[ 2] + m_Value[ 9]*m.m_Value[ 6] + m_Value[10]*m.m_Value[10] + m_Value[11]*m.m_Value[14];
		Matrix.m_Value[11] = m_Value[ 8]*m.m_Value[ 3] + m_Value[ 9]*m.m_Value[ 7] + m_Value[10]*m.m_Value[11] + m_Value[11]*m.m_Value[15];

		Matrix.m_Value[12] = m_Value[12]*m.m_Value[ 0] + m_Value[13]*m.m_Value[ 4] + m_Value[14]*m.m_Value[ 8] + m_Value[15]*m.m_Value[12];
		Matrix.m_Value[13] = m_Value[12]*m.m_Value[ 1] + m_Value[13]*m.m_Value[ 5] + m_Value[14]*m.m_Value[ 9] + m_Value[15]*m.m_Value[13];
		Matrix.m_Value[14] = m_Value[12]*m.m_Value[ 2] + m_Value[13]*m.m_Value[ 6] + m_Value[14]*m.m_Value[10] + m_Value[15]*m.m_Value[14];
		Matrix.m_Value[15] = m_Value[12]*m.m_Value[ 3] + m_Value[13]*m.m_Value[ 7] + m_Value[14]*m.m_Value[11] + m_Value[15]*m.m_Value[15];

		return Matrix;
	}

	CMatrix4x4 operator*= (const CMatrix4x4 & m)
	{
		return (*this = *this * m);
	}

	CMatrix4x4 operator/ (const T s) const
	{
		CMatrix4x4 m (*this);
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			m.m_Value[i] /= s;
		return m;
	}

	CMatrix4x4 operator/= (const T s)
	{
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			m_Value[i] /= s;
		return *this;
	}

	CMatrix4x4 operator- () const
	{
		CMatrix4x4<T> Matrix;
		for (unsigned char i=0; i<(GTL_MATRIX_4X4_RANG * GTL_MATRIX_4X4_RANG); i++)
			Matrix.m_Value[i] = -m_Value[i];
		return Matrix;
	}

	CMatrix4x4 GetIdentity ()
	{
		CMatrix4x4<T> Matrix;
		return Matrix.Identity ();
	}

	void Identity ()
	{
		m_Value[ 0] = static_cast<T> (1); m_Value[ 1] = static_cast<T> (0); m_Value[ 2] = static_cast<T> (0); m_Value[ 3] = static_cast<T> (0);
		m_Value[ 4] = static_cast<T> (0); m_Value[ 5] = static_cast<T> (1); m_Value[ 6] = static_cast<T> (0); m_Value[ 7] = static_cast<T> (0);
		m_Value[ 8] = static_cast<T> (0); m_Value[ 9] = static_cast<T> (0); m_Value[10] = static_cast<T> (1); m_Value[11] = static_cast<T> (0);
		m_Value[12] = static_cast<T> (0); m_Value[13] = static_cast<T> (0); m_Value[14] = static_cast<T> (0); m_Value[15] = static_cast<T> (1);
	}

	CMatrix4x4 GetScale (const T x, const T y, const T z)
	{
		CMatrix4x4<T> Matrix (
			gtl::CVector4<float>(x, 0, 0, 0),
			gtl::CVector4<float>(0, y, 0, 0),
			gtl::CVector4<float>(0, 0, z, 0),
			gtl::CVector4<float>(0, 0, 0, 1));
		return Matrix;
	}

	void Scale (const T x, const T y, const T z)
	{
		*this = GetScale (x, y, z);
	}

	CMatrix4x4 GetTranslate (const T x, const T y, const T z)
	{
		CMatrix4x4<T> Matrix (
			gtl::CVector4<float>(1, 0, 0, 0),
			gtl::CVector4<float>(0, 1, 0, 0),
			gtl::CVector4<float>(0, 0, 1, 0),
			gtl::CVector4<float>(x, y, z, 1));
		return Matrix;
	}

	void Translate (const T x, const T y, const T z)
	{
		*this = GetTranslate (x, y, z);
	}

	CMatrix4x4 GetRotateX (const T angle)
	{
		T c = cos (angle * static_cast<T>(PI_OVER_180));
		T s = sin (angle * static_cast<T>(PI_OVER_180));
		CMatrix4x4<T> Matrix (
			gtl::CVector4<float>(1, 0, 0, 0),
			gtl::CVector4<float>(0, c, s, 0),
			gtl::CVector4<float>(0,-s, c, 0),
			gtl::CVector4<float>(0, 0, 0, 1));
		return Matrix;
	}

	void RotateX (const T angle)
	{
		*this = GetRotateX (angle);
	}

	CMatrix4x4 GetRotateY (const T angle)
	{
		T c = cos (angle * static_cast<T>(PI_OVER_180));
		T s = sin (angle * static_cast<T>(PI_OVER_180));
		CMatrix4x4<T> Matrix (
			gtl::CVector4<float>(c, 0,-s, 0),
			gtl::CVector4<float>(0, 1, 0, 0),
			gtl::CVector4<float>(s, 0, c, 0),
			gtl::CVector4<float>(0, 0, 0, 1));
		return Matrix;
	}

	void RotateY (const T angle)
	{
		*this = GetRotateY (angle);
	}

	CMatrix4x4 GetRotateZ (const T angle)
	{
		T c = cos (angle * static_cast<T>(PI_OVER_180));
		T s = sin (angle * static_cast<T>(PI_OVER_180));
		CMatrix4x4<T> Matrix (
			gtl::CVector4<float>( c, s, 0, 0),
			gtl::CVector4<float>(-s, c, 0, 0),
			gtl::CVector4<float>( 0, 0, 1, 0),
			gtl::CVector4<float>( 0, 0, 0, 1));
		return Matrix;
	}

	void RotateZ (const T angle)
	{
		*this = GetRotateZ (angle);
	}

	CMatrix4x4 GetRotate (float fAngle, CVector3<T> Axis)
	{
		CMatrix4x4<T> Matrix;

		T s = static_cast<T> (sin (DEG_TO_RAD(fAngle)));
		T c = static_cast<T> (cos (DEG_TO_RAD(fAngle)));

		Axis.Normalize ();

		T ux = Axis (X);
		T uy = Axis (Y);
		T uz = Axis (Z);
    
		Matrix.m_Value[0]  = c + (1 - c) * ux;
		Matrix.m_Value[1]  = (1 - c) * ux * uy + s * uz;
		Matrix.m_Value[2]  = (1 - c) * ux * uz - s * uy;
		Matrix.m_Value[3]  = 0;
    
		Matrix.m_Value[4]  = (1 - c) * uy * ux - s * uz;
		Matrix.m_Value[5]  = c + (1 - c) * pow (uy, 2);
		Matrix.m_Value[6]  = (1 - c) * uy * uz + s * ux;
		Matrix.m_Value[7]  = 0;
    
		Matrix.m_Value[8]  = (1 - c) * uz * ux + s * uy;
		Matrix.m_Value[9]  = (1 - c) * uz * uz - s * ux;
		Matrix.m_Value[10] = c + (1 - c) * pow (uz, 2);
		Matrix.m_Value[11] = 0;
    
		Matrix.m_Value[12] = 0;
		Matrix.m_Value[13] = 0;
		Matrix.m_Value[14] = 0;
		Matrix.m_Value[15] = 1;

		return Matrix;
	}

	void Rotate (float fAngle, CVector3<T> axis)
	{
		*this = GetRotate (fAngle, axis);
	}
};

}; // namespace gtl

#endif //GTL_MATRIX_4X4_H
