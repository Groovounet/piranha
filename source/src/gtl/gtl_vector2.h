//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_vector2.h
//! \brief Classe CVector2, un vecteur à 2 dimensions.
//////////////////////////////////////////////////////////////////////////////

// v : Name of a vector variable (CVector2<T>)
// a : Name of an array variable (T*)
// s : Name of a scalar variable (T)

#ifndef GTL_VECTOR_2_H
#define GTL_VECTOR_2_H

#include "gtl_math.h"
#include "gtl_vector.h"

namespace gtl {

#define GTL_VECTOR_2_RANG 2

//! \brief Un vecteur à 2 dimensions.
template <typename T> class CVector2
{
private:
	T m_Value[GTL_VECTOR_2_RANG];

public:
	CVector2 ()
	{
		m_Value[0] = 0;
		m_Value[1] = 0;
	}
	
	CVector2 (const T x, const T y)
	{
		m_Value[0] = x;
		m_Value[1] = y;
	}
	
	CVector2 (const CVector2<T>& v)
	{
		m_Value[0] = v.m_Value[0];
		m_Value[1] = v.m_Value[1];
	} 
	
	CVector2 (const T a[GTL_VECTOR_2_RANG])
	{
		m_Value[0] = a[0];
		m_Value[1] = a[1];
	}

	inline CVector2<T>& operator= (const CVector2<T>& v)
	{
		m_Value[0] = v.m_Value[0];
		m_Value[1] = v.m_Value[1];
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

	inline const bool operator== (const CVector2<T>& v) const
	{
		return (m_Value[0] == v.m_Value[0] && m_Value[1] == v.m_Value[1]);
	}
	
	inline const bool operator!= (const CVector2<T>& v) const
	{
		return !(*this == v);
	}
	
	inline const bool operator> (const CVector2<T>& v) const
	{
		return (Magnitude () > v.Magnitude ());
	}
	
	inline const bool operator< (const CVector2<T>& v) const
	{
		return (Magnitude () < v.Magnitude ());
	}
	
	inline const bool operator>= (const CVector2<T>& v) const
	{
		return (Magnitude () >= v.Magnitude ());
	}
	
	inline const bool operator<= (const CVector2<T>& v) const
	{
		return (Magnitude () <= v.Magnitude ());
	}

	inline CVector2<T> operator+ (const CVector2<T>& v) const
	{
		return CVector2<T> (
			m_Value[0] + v.m_Value[0],
			m_Value[1] + v.m_Value[1]
		);
	}
	
	inline CVector2<T>& operator+= (const CVector2<T>& v)
	{
		m_Value[0] += v.m_Value[0];
		m_Value[1] += v.m_Value[1];
		return *this;
	}

	inline CVector2<T> operator- (const CVector2<T>& v) const
	{
		return CVector2<T> (
			m_Value[0] - v.m_Value[0],
			m_Value[1] - v.m_Value[1]
		);
	}

	inline CVector2<T>& operator-= (const CVector2<T>& v)
	{
		m_Value[0] -= v.m_Value[0];
		m_Value[1] -= v.m_Value[1];
		return *this;
	}
	
	inline CVector2<T> operator* (const T s) const
	{
		return CVector2<T> (
			m_Value[0] * s,
			m_Value[1] * s
		);
	}
	
	inline CVector2<T>& operator*= (const T s)
	{
		m_Value[0] *= s;
		m_Value[1] *= s;
		return *this;
	}

	inline CVector2<T> operator/ (const T s) const
	{
		return CVector2<T> (
			m_Value[0] / s,
			m_Value[1] / s
		);
	}
	
	inline CVector2<T>& operator/= (const T s)
	{
		m_Value[0] /= s;
		m_Value[1] /= s;
		return *this;
	}

	inline T GetDot (const CVector2<T>& v) const
	{
		return (m_Value[0] * v.m_Value[0] + m_Value[1] * v.m_Value[1]);
	}

	inline T operator% (const CVector2<T>& v) const
	{
		return GetDot (v);
	}

	inline T operator* (const CVector2<T>& v) const
	{
		return GetDot (v);
	}

	inline T Magnitude () const
	{
		return static_cast<T> (sqrt (MagnitudeSquared ()));
	}

	inline T MagnitudeSquared () const
	{
		return SQR (m_Value[0]) + SQR (m_Value[1]);
	}

	inline CVector2<T> GetNormalize () const
	{
		T VecLen = Magnitude ();
		if (VecLen == 0) 
			return CVector2<T> (0, 0);
		return CVector2<T> (m_Value[0] / VecLen, m_Value[1] / VecLen);
	}

	inline CVector2<T>& Normalize ()
	{
		T VecLen = Magnitude ();
		if (VecLen != 0) 
		{
			m_Value[0] /= VecLen;
			m_Value[1] /= VecLen;
		}
		return *this;
	}

	inline CVector2<T> GetInvert () const
	{
		return CVector2<T> (-m_Value[0], -m_Value[1]);
	}

	inline CVector2<T> operator- () const
	{
		return GetInvert ();
	}

	inline CVector2<T>& Invert ()
	{
		m_Value[0] = -m_Value[0];
		m_Value[1] = -m_Value[1];
		return *this;
	}

	inline CVector2<T>& Saturation (const T min, const T max)
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

		return *this;
	}

	inline CVector2<T> GetSaturation (const T min, const T max)
	{
		if (min >= max)
			return *this;

		CVector2 Return = *this;

		if (Return.m_Value[0] < min)
			Return.m_Value[0] = min;
		if (Return.m_Value[0] > max)
			Return.m_Value[0] > max;

		if (Return.m_Value[1] < min)
			Return.m_Value[1] = min;
		if (Return.m_Value[1] > max)
			Return.m_Value[1] > max;

		return Return;
	}

	inline CVector2<T>& Absolute ()
	{
		if (m_Value[0] < 0) m_Value[0] = -m_Value[0];
		if (m_Value[1] < 0) m_Value[0] = -m_Value[1];
	}

	inline CVector2<T> GetAbsolute ()
	{
		CVector2 Return;

		Return.m_Value[0] = (m_Value[0] < 0) ? -m_Value[0] : m_Value[0];
		Return.m_Value[1] = (m_Value[1] < 0) ? -m_Value[1] : m_Value[1];

		return Return;
	}

	inline CVector2<T>& Max (const CVector2<T> & v)
	{
		m_Value[0] = m_Value[0] > v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		m_Value[1] = m_Value[1] > v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		return *this;
	}

	inline CVector2<T> GetMax (const CVector2<T> & v)
	{
		CVector2 Return;
		Return.m_Value[0] = m_Value[0] > v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		Return.m_Value[1] = m_Value[1] > v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		return Return;
	}

	inline CVector2<T>& Min (const CVector2<T> & v)
	{
		m_Value[0] = m_Value[0] > v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		m_Value[1] = m_Value[1] > v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		return *this;
	}

	inline CVector2<T> GetMin (const CVector2<T> & v)
	{
		CVector2 Return;
		Return.m_Value[0] = m_Value[0] < v.m_Value[0] ? m_Value[0] : v.m_Value[0];
		Return.m_Value[1] = m_Value[1] < v.m_Value[1] ? m_Value[1] : v.m_Value[1];
		return Return;
	}

	inline CVector2<T>& Clamp (const CVector2<T> & min, const CVector2<T> & max)
	{
		m_Value[0] = min[0] < m_Value[0] ? min[0] : max[0] > m_Value[0] ? max[0] : m_Value[0];
		m_Value[1] = min[1] < m_Value[1] ? min[1] : max[1] > m_Value[1] ? max[1] : m_Value[1];
		return *this;
	}

	inline CVector2<T> GetClamp (const CVector2<T> & min, const CVector2<T> & max)
	{
		CVector2 Return;
		Return.m_Value[0] = min[0] < m_Value[0] ? min[0] : max[0] > m_Value[0] ? max[0] : m_Value[0];
		Return.m_Value[1] = min[1] < m_Value[1] ? min[1] : max[1] > m_Value[1] ? max[1] : m_Value[1];
		return Return;
	}

	inline CVector2<T>& Mad (const CVector2<T> & v1, const CVector2<T> & v2)
	{
		m_Value[0] = m_Value[0] * v1.m_Value[0] + v2.m_Value[0];
		m_Value[1] = m_Value[1] * v1.m_Value[1] + v2.m_Value[1];
		return *this;
	}

	inline CVector2<T> GetMad (const CVector2<T> & v1, const CVector2<T> & v2)
	{
		CVector2 Return;
		Return.m_Value[0] = m_Value[0] * v1.m_Value[0] + v2.m_Value[0];
		Return.m_Value[1] = m_Value[1] * v1.m_Value[1] + v2.m_Value[1];
		return Return;
	}

	inline CVector2<T> Distance (const CVector2<T> & v1, const CVector2<T> & v2)
	{
		CVector2 v = v2 - v1;
		return sqrt (SQL(v.m_Value[0]) + SQL(v.m_Value[1]));
	}

	inline CVector2<T> DistanceSquared (const CVector2<T> & v1, const CVector2<T> & v2)
	{
		CVector2 v = v2 - v1;
		return (SQL(v.m_Value[0]) + SQL(v.m_Value[1]));
	}

	//! 
	inline CVector2<T> Proj (const CVector2<T> & Normal)
	{
		return *this = (GetDot (Normal) / Normal.GetDot (Normal)) * Normal;
	}

	inline CVector2<T> GetProj (const CVector2<T> & Normal) const
	{
		return (*this % Normal) / (Normal % Normal) * Normal;
	}

	inline CVector2<T> Perp (const CVector2<T> & Normal)
	{
		return *this = (*this - GetProj (Normal));
	}

	inline CVector2<T> GetPerp (const CVector2<T> & Normal) const
	{
		return *this - GetProj (Normal);
	}
};

template <typename T> CVector2<T> operator* (const T s, const CVector2<T>& v)
{
	return v * nb;
}

}; // namespace gtl

#endif //GTL_VECTOR_2_H
