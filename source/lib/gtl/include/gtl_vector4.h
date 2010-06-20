//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_vector4.h
//! \brief Classe CVector4, un vecteur à 4 dimensions.
//////////////////////////////////////////////////////////////////////////////

// v : Name of a vector variable (CVector4<T>)
// a : Name of an array variable (T*)
// s : Name of a scalar variable (T)

#ifndef GTL_VECTOR_4_H
#define GTL_VECTOR_4_H

#include "gtl_math.h"
#include "gtl_vector.h"

namespace gtl {

#define GTL_VECTOR_4_RANG 4

//! \brief Un vecteur à 4 dimensions.
template <typename T> class CVector4
{
private:
	T m_Value[GTL_VECTOR_4_RANG];

public:
	CVector4 ()
	{
		m_Value[0] = 0;
		m_Value[1] = 0;
		m_Value[2] = 0;
		m_Value[3] = 0;
	}

	CVector4 (const T x, const T y, const T z, const T w)
	{
		m_Value[0] = x;
		m_Value[1] = y;
		m_Value[2] = z;
		m_Value[3] = w;
	}

	CVector4 (const CVector4<T>& v)
	{
		m_Value[0] = v.m_Value[0];
		m_Value[1] = v.m_Value[1];
		m_Value[2] = v.m_Value[2];
		m_Value[3] = v.m_Value[3];
	} 

	CVector4 (const T a[GTL_VECTOR_4_RANG])
	{
		m_Value[0] = a[0];
		m_Value[1] = a[1];
		m_Value[2] = a[2];
		m_Value[3] = a[3];
	}

	inline CVector4<T>& operator= (const CVector4<T>& v)
	{
		m_Value[0] = v.m_Value[0];
		m_Value[1] = v.m_Value[1];
		m_Value[2] = v.m_Value[2];
		m_Value[3] = v.m_Value[3];
		return *this;
	}

	//! Accès aux coordonnées du vecteur.
	inline T& operator() (const TCoord & Coord)
	{
		return m_Value[Coord];
	}

	inline T operator() (const TCoord & Coord) const
	{
		return m_Value[Coord];
	}

	//! Accès aux coordonnées du vecteur.
	inline operator T* ()
	{
		return m_Value;
	}

	//! Accès aux coordonnées du vecteur.
	inline operator const T* () const
	{
		return m_Value;
	}

	inline const bool operator== (const CVector4<T>& v) const
	{
		return (m_Value[0] == v.m_Value[0] 
			&&	m_Value[1] == v.m_Value[1] 
			&&	m_Value[2] == v.m_Value[2] 
			&&	m_Value[3] == v.m_Value[3]);
	}

	inline const bool operator!= (const CVector4<T>& v) const
	{
		return !(*this==v);
	}

	inline const bool operator> (const CVector4<T>& v) const
	{
		return (Magnitude () > v.Magnitude ());
	}

	inline const bool operator< (const CVector4<T>& v) const
	{
		return (Magnitude () < v.Magnitude ());
	}

	inline const bool operator>= (const CVector4<T>& v) const
	{
		return (Magnitude () >= v.Magnitude ());
	}

	inline const bool operator<= (const CVector4<T>& v) const
	{
		return (Magnitude () <= v.Magnitude ());
	}

	inline CVector4<T> operator+ (const CVector4<T>& v) const
	{
		return CVector4<T> (
			m_Value[0] + v.m_Value[0], 
			m_Value[1] + v.m_Value[1], 
			m_Value[2] + v.m_Value[2], 
			m_Value[3] + v.m_Value[3]
		);
	}

	inline CVector4<T>& operator+= (const CVector4<T>& v)
	{
		m_Value[0] += v.m_Value[0];
		m_Value[1] += v.m_Value[1];
		m_Value[2] += v.m_Value[2];
		m_Value[3] += v.m_Value[3];
        return *this;
	}

	inline CVector4<T> operator- (const CVector4<T>& v) const
	{
		return CVector4<T> (
			m_Value[0] - v.m_Value[0],
			m_Value[1] - v.m_Value[1],
			m_Value[2] - v.m_Value[2],
			m_Value[3] - v.m_Value[3]
		);
	}

	inline CVector4<T> operator-= (const CVector4<T>& v)
	{
		m_Value[0] -= v.m_Value[0];
		m_Value[1] -= v.m_Value[1];
		m_Value[2] -= v.m_Value[2];
		m_Value[3] -= v.m_Value[3];
        return *this;
	}

	inline CVector4<T> operator* (const T s) const
	{
		return CVector4<T> (
			m_Value[0] * s,
			m_Value[1] * s,
			m_Value[2] * s,
			m_Value[3] * s
		);
	}

	inline CVector4<T> operator*= (const T s)
	{
		m_Value[0] *= s;
		m_Value[1] *= s;
		m_Value[2] *= s;
		m_Value[3] *= s;
        return *this;
	}

	inline CVector4<T> operator/ (const T s) const
	{
		return CVector4<T> (
			m_Value[0] / s,
			m_Value[1] / s,
			m_Value[2] / s,
			m_Value[3] / s
		);
	}

	inline CVector4<T> operator/= (const T s)
	{
		m_Value[0] /= s;
		m_Value[1] /= s;
		m_Value[2] /= s;
		m_Value[3] /= s;
		return *this;
	}

	inline T Dot (const CVector4<T>& v) const
	{
		return m_Value[0] * v.m_Value[0] + m_Value[1] * v.m_Value[1] + m_Value[2] * v.m_Value[2] + m_Value[3] * v.m_Value[3];
	}

	inline T operator* (const CVector4<T>& v) const
	{
		return Dot (v);
	}

	inline T Magnitude () const
	{
		return static_cast<T> (sqrt (MagnitudeSquared ()));
	}

	inline T MagnitudeSquared () const
	{
		return SQR (m_Value[0]) + SQR (m_Value[1]) + SQR (m_Value[2]) + SQR (m_Value[3]);
	}

	inline CVector4<T> GetNormalize () const
	{
		T VecLen = Magnitude ();
		if (VecLen == 0) 
			return CVector4<T> (0,0,0,1);
		return CVector4<T> (m_Value[0] / VecLen, m_Value[1] / VecLen, m_Value[2] / VecLen, m_Value[3]);
	}

	inline CVector4<T>& Normalize ()
	{
		return *this = GetNormalize ();
	}

	inline CVector4<T> GetInvert ()
	{
		return CVector4<T> (-m_Value[0], -m_Value[1], -m_Value[2], -m_Value[3]);
	}

	inline CVector4<T> operator- () const
	{
		return GetInvert ();
	}

	inline CVector4<T>& Invert ()
	{
		m_Value[0] = -m_Value[0];
		m_Value[1] = -m_Value[1];
		m_Value[2] = -m_Value[2];
		m_Value[3] = -m_Value[3];
		return *this;
	}

	inline CVector4<T>& Saturation (const T min, const T max)
	{
		if (min >= max)
			return *this;

		if (m_Value[0] < min)
			m_Value[0] = min;
		if (m_Value[0] > max)
			m_Value[0] > max;

		if (m_Value[1] < min)
			m_Value[1] = min;
		if (m_Value[1] > max)
			m_Value[1] > max;

		if (m_Value[2] < min)
			m_Value[2] = min;
		if (m_Value[2] > max)
			m_Value[2] > max;

		if (m_Value[3] < min)
			m_Value[3] = min;
		if (m_Value[3] > max)
			m_Value[3] > max;

		return *this;
	}

	inline CVector4<T> GetSaturation (const T min, const T max)
	{
		if (min >= max)
			return *this;

		CVector4 Return = *this;

		if (Return.m_Value[0] < min)
			Return.m_Value[0] = min;
		if (Return.m_Value[0] > max)
			Return.m_Value[0] > max;

		if (Return.m_Value[1] < min)
			Return.m_Value[1] = min;
		if (Return.m_Value[1] > max)
			Return.m_Value[1] > max;

		if (m_Value[2] < min)
			m_Value[2] = min;
		if (m_Value[2] > max)
			m_Value[2] > max;

		if (m_Value[3] < min)
			m_Value[3] = min;
		if (m_Value[3] > max)
			m_Value[3] > max;

		return Return;
	}

	inline CVector4<T>& Absolute ()
	{
		if (m_Value[0] < 0) m_Value[0] = -m_Value[0];
		if (m_Value[1] < 0) m_Value[0] = -m_Value[1];
		if (m_Value[2] < 0) m_Value[0] = -m_Value[2];
		if (m_Value[3] < 0) m_Value[0] = -m_Value[3];
	}

	inline CVector4<T> GetAbsolute ()
	{
		CVector4 Return;

		Return.m_Value[0] = (m_Value[0] < 0) ? -m_Value[0] : m_Value[0];
		Return.m_Value[1] = (m_Value[1] < 0) ? -m_Value[1] : m_Value[1];
		Return.m_Value[2] = (m_Value[2] < 0) ? -m_Value[2] : m_Value[2];
		Return.m_Value[3] = (m_Value[3] < 0) ? -m_Value[3] : m_Value[3];

		return Return;
	}

	inline CVector4<T>& Max (const CVector4<T>& v)
	{
		m_Value[0] = m_Value[0] > v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		m_Value[1] = m_Value[1] > v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		m_Value[2] = m_Value[2] > v.m_Value[2] ? m_Value[2] : v.m_Value[2];
		m_Value[3] = m_Value[3] > v.m_Value[3] ? m_Value[3] : v.m_Value[3];
		return *this;
	}

	inline CVector4<T> GetMax (const CVector4<T>& v)
	{
		CVector4 Return;
		Return.m_Value[0] = m_Value[0] > v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		Return.m_Value[1] = m_Value[1] > v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		Return.m_Value[2] = m_Value[2] > v.m_Value[2] ? m_Value[2] : v.m_Value[2];
		Return.m_Value[3] = m_Value[3] > v.m_Value[3] ? m_Value[3] : v.m_Value[3];
		return Return;
	}

	inline CVector4<T>& Min (const CVector4<T>& v)
	{
		m_Value[0] = m_Value[0] > v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		m_Value[1] = m_Value[1] > v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		m_Value[2] = m_Value[2] > v.m_Value[2] ? m_Value[2] : v.m_Value[2];
		m_Value[3] = m_Value[3] > v.m_Value[3] ? m_Value[3] : v.m_Value[3];
		return *this;
	}

	inline CVector4<T> GetMin (const CVector4<T>& v)
	{
		CVector4 Return;
		Return.m_Value[0] = m_Value[0] < v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		Return.m_Value[1] = m_Value[1] < v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		Return.m_Value[2] = m_Value[2] < v.m_Value[2] ? m_Value[2] : v.m_Value[2];
		Return.m_Value[3] = m_Value[3] < v.m_Value[3] ? m_Value[3] : v.m_Value[3];
		return Return;
	}

	inline CVector4<T>& Clamp (const CVector4<T> & min, const CVector4<T> & max)
	{
		m_Value[0] = min[0] < m_Value[0] ? min[0] : max[0] > m_Value[0] ? max[0] : m_Value[0];
		m_Value[1] = min[1] < m_Value[1] ? min[1] : max[1] > m_Value[1] ? max[1] : m_Value[1];
		m_Value[2] = min[2] < m_Value[2] ? min[2] : max[2] > m_Value[2] ? max[2] : m_Value[2];
		m_Value[3] = min[3] < m_Value[3] ? min[3] : max[3] > m_Value[3] ? max[3] : m_Value[3];
		return *this;
	}

	inline CVector4<T> GetClamp (const CVector4<T> & min, const CVector4<T> & max)
	{
		CVector4 Return;
		Return.m_Value[0] = min[0] < m_Value[0] ? min[0] : max[0] > m_Value[0] ? max[0] : m_Value[0];
		Return.m_Value[1] = min[1] < m_Value[1] ? min[1] : max[1] > m_Value[1] ? max[1] : m_Value[1];
		Return.m_Value[2] = min[2] < m_Value[2] ? min[2] : max[2] > m_Value[2] ? max[2] : m_Value[2];
		Return.m_Value[3] = min[3] < m_Value[3] ? min[3] : max[3] > m_Value[3] ? max[3] : m_Value[3];
		return Return;
	}

	inline CVector4<T>& Mad (const CVector4<T> & v1, const CVector4<T> & v2)
	{
		m_Value[0] = m_Value[0] * v1.m_Value[0] + v2.m_Value[0];
		m_Value[1] = m_Value[1] * v1.m_Value[1] + v2.m_Value[1];
		m_Value[2] = m_Value[2] * v1.m_Value[2] + v2.m_Value[2];
		m_Value[3] = m_Value[3] * v1.m_Value[3] + v2.m_Value[3];
		return *this;
	}

	inline CVector4<T> GetMad (const CVector4<T> & v1, const CVector4<T> & v2)
	{
		CVector4 Return;
		Return.m_Value[0] = m_Value[0] * v1.m_Value[0] + v2.m_Value[0];
		Return.m_Value[1] = m_Value[1] * v1.m_Value[1] + v2.m_Value[1];
		Return.m_Value[2] = m_Value[2] * v1.m_Value[2] + v2.m_Value[2];
		Return.m_Value[3] = m_Value[3] * v1.m_Value[3] + v2.m_Value[3];
		return Return;
	}
};

template <typename T> CVector4<T> operator* (const T s, const CVector4<T>& v)
{
	return v * nb;
}

}; // namespace gtl

#endif //GTL_VECTOR_4_H
