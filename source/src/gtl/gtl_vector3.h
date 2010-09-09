//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_vector3.h
//! \brief Classe CVector3, un vecteur à 3 dimensions.
//////////////////////////////////////////////////////////////////////////////

// v : Name of a vector variable (CVector3<T>)
// a : Name of an array variable (T*)
// s : Name of a scalar variable (T)

#ifndef GTL_VECTOR_3_H
#define GTL_VECTOR_3_H

#include "gtl_math.h"
#include "gtl_vector.h"

namespace gtl {

#define GTL_VECTOR_3_RANG 3

//! \brief Un vecteur à 3 dimensions.
template <typename T> class CVector3
{
private:
	T m_Value[GTL_VECTOR_3_RANG];

public:
	CVector3 ()
	{
		m_Value[0] = 0;
		m_Value[1] = 0;
		m_Value[2] = 0;
	}

	CVector3 (const T x, const T y, const T z)
	{
		m_Value[0] = x;
		m_Value[1] = y;
		m_Value[2] = z;
	}

	CVector3 (const CVector3<T>& v)
	{
		m_Value[0] = v.m_Value[0];
		m_Value[1] = v.m_Value[1];
		m_Value[2] = v.m_Value[2];
	}

	CVector3 (const T a[GTL_VECTOR_3_RANG])
	{
		m_Value[0] = a[0];
		m_Value[1] = a[1];
		m_Value[2] = a[2];
	}

	inline CVector3<T>& operator= (const CVector3<T>& v)
	{
		m_Value[0] = v.m_Value[0];
		m_Value[1] = v.m_Value[1];
		m_Value[2] = v.m_Value[2];
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

	inline bool operator== (const CVector3<T>& v) const
	{
		return (m_Value[0] == v.m_Value[0]
			&& m_Value[1] == v.m_Value[1]
			&& m_Value[2] == v.m_Value[2]
		);
	}

	inline bool operator!= (const CVector3<T>& v) const
	{
		return !(*this==v);
	}

	inline const bool operator> (const CVector3<T>& v) const
	{
		return (Magnitude () > v.Magnitude ());
	}

	inline const bool operator< (const CVector3<T>& v) const
	{
		return (Magnitude () < v.Magnitude ());
	}

	inline const bool operator>= (const CVector3<T>& v) const
	{
		return (Magnitude () >= v.Magnitude ());
	}

	inline const bool operator<= (const CVector3<T>& v) const
	{
		return (Magnitude () <= v.Magnitude ());
	}

	inline CVector3<T> operator+ (const CVector3<T>& v) const
	{
		return CVector3<T> (
			m_Value[0] + v.m_Value[0],
			m_Value[1] + v.m_Value[1],
			m_Value[2] + v.m_Value[2]
		);
	}

	inline CVector3<T>& operator+= (const CVector3<T>& v)
	{
		m_Value[0] += v.m_Value[0];
		m_Value[1] += v.m_Value[1];
		m_Value[2] += v.m_Value[2];
		return *this;
	}

	inline CVector3<T> operator- (const CVector3<T>& v) const
	{
		return CVector3<T> (
			m_Value[0] - v.m_Value[0],
			m_Value[1] - v.m_Value[1],
			m_Value[2] - v.m_Value[2]
		);
	}

	inline CVector3<T>& operator-= (const CVector3<T>& v)
	{
		m_Value[0] -= v.m_Value[0];
		m_Value[1] -= v.m_Value[1];
		m_Value[2] -= v.m_Value[2];
		return *this;
	}

	inline CVector3<T> operator* (const T s) const
	{
		return CVector3<T> (
			m_Value[0] * s,
			m_Value[1] * s,
			m_Value[2] * s
		);
	}

	inline CVector3<T>& operator*= (const T s)
	{
		m_Value[0] *= s;
		m_Value[1] *= s;
		m_Value[2] *= s;
		return *this;
	}

	inline CVector3<T> operator* (const CVector3<T>& v) const
	{
		return GetCross (v);
	}

	inline CVector3<T>& operator*= (const CVector3<T>& v)
	{
		return (*this = GetCross (v));
	}

	inline CVector3<T> operator/ (const T s) const
	{
		return CVector3<T> (
			m_Value[0] / s,
			m_Value[1] / s,
			m_Value[2] / s
		);
	}

	inline CVector3<T>& operator/= (const T s)
	{
		m_Value[0] /= s;
		m_Value[1] /= s;
		m_Value[2] /= s;
		return *this;
	}

	inline T GetDot (const CVector3<T>& v) const
	{
		return (m_Value[0] * v.m_Value[0] + m_Value[1] * v.m_Value[1] + m_Value[2] * v.m_Value[2]);
	}

	inline T operator% (const CVector3<T>& v) const
	{
		return GetDot (v);
	}

	inline CVector3<T> GetCross (const CVector3<T>& v) const
	{
		return CVector3<T> (
			m_Value[1] * v.m_Value[2] -	m_Value[2] * v.m_Value[1],
			m_Value[2] * v.m_Value[0] - m_Value[0] * v.m_Value[2],
			m_Value[0] * v.m_Value[1] - m_Value[1] * v.m_Value[0]
		);
	}

	inline CVector3<T> operator^ (const CVector3<T>& v) const
	{
		return GetCross (v);
	}

	inline CVector3<T>& Cross (const CVector3<T>& v)
	{
		return (*this = GetCross (v));
	}

	inline CVector3<T>& operator^= (const CVector3<T>& v)
	{
		Cross (v);
		return *this;
	}

	inline T Magnitude () const
	{
		return static_cast<T> (sqrt (MagnitudeSquared ()));
	}

	inline T MagnitudeSquared () const
	{
		return SQR (m_Value[0]) + SQR (m_Value[1]) + SQR (m_Value[2]);
	}

	inline CVector3<T> GetNormalize () const
	{
		T VecLen = Magnitude ();
		if (VecLen == 0)
			return CVector3<T> (0,0,0);
		return CVector3<T> (m_Value[0] / VecLen, m_Value[1] / VecLen, m_Value[2] / VecLen);
	}

	inline CVector3<T>& Normalize ()
	{
		T VecLen = Magnitude ();
		if (VecLen != 0)
		{
			m_Value[0] /= VecLen;
			m_Value[1] /= VecLen;
			m_Value[2] /= VecLen;
		}
		return *this;
	}

	inline CVector3<T> GetInvert () const
	{
		return CVector3<T> (-m_Value[0], -m_Value[1], -m_Value[2]);
	}

	inline CVector3<T> operator- () const
	{
		return GetInvert ();
	}

	inline CVector3<T>& Invert ()
	{
		m_Value[0] = -m_Value[0];
		m_Value[1] = -m_Value[1];
		m_Value[2] = -m_Value[2];
		return *this;
	}

	inline CVector3<T>& Saturation (const T min, const T max)
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

		return *this;
	}

	inline CVector3<T> GetSaturation (const T min, const T max)
	{
		if (min >= max)
			return *this;

		CVector3 Return = *this;

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

		return Return;
	}

	inline CVector3<T>& Absolute ()
	{
		if (m_Value[0] < 0) m_Value[0] = -m_Value[0];
		if (m_Value[1] < 0) m_Value[0] = -m_Value[1];
		if (m_Value[2] < 0) m_Value[0] = -m_Value[2];
	}

	inline CVector3<T> GetAbsolute ()
	{
		CVector3 Return;

		Return.m_Value[0] = (m_Value[0] < 0) ? -m_Value[0] : m_Value[0];
		Return.m_Value[1] = (m_Value[1] < 0) ? -m_Value[1] : m_Value[1];
		Return.m_Value[2] = (m_Value[2] < 0) ? -m_Value[2] : m_Value[2];

		return Return;
	}

	inline CVector3<T>& Max (const CVector3<T> & v)
	{
		m_Value[0] = m_Value[0] > v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		m_Value[1] = m_Value[1] > v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		m_Value[2] = m_Value[2] > v.m_Value[2] ? m_Value[2] : v.m_Value[2];
		return *this;
	}

	inline CVector3<T> GetMax (const CVector3<T> & v)
	{
		CVector3 Return;
		Return.m_Value[0] = m_Value[0] > v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		Return.m_Value[1] = m_Value[1] > v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		Return.m_Value[2] = m_Value[2] > v.m_Value[2] ? m_Value[2] : v.m_Value[2];
		return Return;
	}

	inline CVector3<T>& Min (const CVector3<T> & v)
	{
		m_Value[0] = m_Value[0] > v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		m_Value[1] = m_Value[1] > v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		m_Value[2] = m_Value[2] > v.m_Value[2] ? m_Value[2] : v.m_Value[2];
		return *this;
	}

	inline CVector3<T> GetMin (const CVector3<T> & v)
	{
		CVector3 Return;
		Return.m_Value[0] = m_Value[0] < v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		Return.m_Value[1] = m_Value[1] < v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		Return.m_Value[2] = m_Value[2] < v.m_Value[2] ? m_Value[2] : v.m_Value[2];
		return Return;
	}

	inline CVector3<T>& Clamp (const CVector3<T> & min, const CVector3<T> & max)
	{
		m_Value[0] = min[0] < m_Value[0] ? min[0] : max[0] > m_Value[0] ? max[0] : m_Value[0];
		m_Value[1] = min[1] < m_Value[1] ? min[1] : max[1] > m_Value[1] ? max[1] : m_Value[1];
		m_Value[2] = min[2] < m_Value[2] ? min[2] : max[2] > m_Value[2] ? max[2] : m_Value[2];
		return *this;
	}

	inline CVector3<T> GetClamp (const CVector3<T> & min, const CVector3<T> & max)
	{
		CVector3 Return;
		Return.m_Value[0] = min[0] < m_Value[0] ? min[0] : max[0] > m_Value[0] ? max[0] : m_Value[0];
		Return.m_Value[1] = min[1] < m_Value[1] ? min[1] : max[1] > m_Value[1] ? max[1] : m_Value[1];
		Return.m_Value[2] = min[2] < m_Value[2] ? min[2] : max[2] > m_Value[2] ? max[2] : m_Value[2];
		return Return;
	}

	inline CVector3<T>& Mad (const CVector3<T> & v1, const CVector3<T> & v2)
	{
		m_Value[0] = m_Value[0] * v1.m_Value[0] + v2.m_Value[0];
		m_Value[1] = m_Value[1] * v1.m_Value[1] + v2.m_Value[1];
		m_Value[2] = m_Value[2] * v1.m_Value[2] + v2.m_Value[2];
		return *this;
	}

	inline CVector3<T> GetMad (const CVector3<T> & v1, const CVector3<T> & v2)
	{
		CVector3 Return;
		Return.m_Value[0] = m_Value[0] * v1.m_Value[0] + v2.m_Value[0];
		Return.m_Value[1] = m_Value[1] * v1.m_Value[1] + v2.m_Value[1];
		Return.m_Value[2] = m_Value[2] * v1.m_Value[2] + v2.m_Value[2];
		return Return;
	}

	inline CVector3<T> Proj (const CVector3<T> & Normal)
	{
		return *this = (GetDot (Normal) / Normal.GetDot (Normal)) * Normal;
	}

	inline CVector3<T> GetProj (const CVector3<T> & Normal) const
	{
		return (*this % Normal) / (Normal % Normal) * Normal;
	}

	inline CVector3<T> Perp (const CVector3<T> & Normal)
	{
		return *this = (*this - GetProj (Normal));
	}

	inline CVector3<T> GetPerp (const CVector3<T> & Normal) const
	{
		return *this - GetProj (Normal);
	}
};

template <typename T> CVector3<T> operator* (const T s, const CVector3<T>& v)
{
	return v * s;
}

}; // namespace gtl

#endif //GTL_VECTOR_3_H
