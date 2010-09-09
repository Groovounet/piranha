//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_color3.h
//! \brief Classe CColor3, pour les couleurs RGB
//////////////////////////////////////////////////////////////////////////////

#ifndef GTL_COLOR_3_H
#define GTL_COLOR_3_H

#include "gtl_color.h"

namespace gtl {

#define GTL_COLOR_3_RANG 3

//! \brief Classe pour l'utilisable de couleurs RGB.
template <typename T> class CColor3
{
private:
	T m_Value[GTL_COLOR_3_RANG];

public:
	CColor3 ()
	{
		m_Value[0] = 0;
		m_Value[1] = 0;
		m_Value[2] = 0;
	}

	CColor3 (const T x, const T y, const T z)
	{
		m_Value[0] = x;
		m_Value[1] = y;
		m_Value[2] = z;
	}

	CColor3 (const CColor3<T> & c)
	{
		m_Value[0] = c.m_Value[0];
		m_Value[1] = c.m_Value[1];
		m_Value[2] = c.m_Value[2];
	}

	CColor3 (unsigned int uiColor)
	{
		m_Value[0] = (uiColor & 0x000000ff);
		m_Value[1] = (uiColor & 0x0000ff00) >> 8;
		m_Value[2] = (uiColor & 0x00ff0000) >> 16;
	}

	CColor3 (const T a[GTL_COLOR_3_RANG])
	{
		m_Value[0] = a[0];
		m_Value[1] = a[1];
		m_Value[2] = a[2];
	}

	inline const bool operator== (const CColor3<T> & c) const
	{
		return (m_Value[0] == c.m_Value[0] 
			&& m_Value[1] == c.m_Value[1]
			&& m_Value[2] == c.m_Value[2]
		);
	}

	inline CColor3& operator= (const CColor3<T> & c)
	{
		m_Value[0] = c.m_Value[0];
		m_Value[1] = c.m_Value[1];
		m_Value[2] = c.m_Value[2];
		return *this;
	}

	inline CColor3& operator= (const T a[GTL_COLOR_3_RANG])
	{
		m_Value[0] = a[0];
		m_Value[1] = a[1];
		m_Value[2] = a[2];
		return *this;
	}

	inline CColor3 operator+ (const CColor3<T> & c) const
	{
		return CColor3<T> (
			m_Value[0] + c.m_Value[0],
			m_Value[1] + c.m_Value[1],
			m_Value[2] + c.m_Value[2]
		);
	}

	inline CColor3& operator+= (const CColor3<T> & c)
	{
		m_Value[0] += v.m_Value[0];
		m_Value[1] += v.m_Value[1];
		m_Value[2] += v.m_Value[2];
		return *this;
	}

	inline CColor3 operator- (const CColor3<T> & c) const
	{
		return CColor3<T> (
			m_Value[0] - c.m_Value[0],
			m_Value[1] - c.m_Value[1],
			m_Value[2] - c.m_Value[2]
		);
	}

	inline CColor3& operator-= (const CColor3<T> & c)
	{
		m_Value[0] -= c.m_Value[0];
		m_Value[1] -= c.m_Value[1];
		m_Value[2] -= c.m_Value[2];
		return *this;
	}

	inline CColor3 operator* (const T s) const
	{
		return CColor3<T> (
			m_Value[0] * s,
			m_Value[1] * s,
			m_Value[2] * s
		);
	}

	inline CColor3& operator*= (const T s)
	{
		m_Value[0] *= s;
		m_Value[1] *= s;
		m_Value[2] *= s;
		return *this;
	}

	inline CColor3 operator/ (const T s) const
	{
		return CColor3<T> (
			m_Value[0] / s,
			m_Value[1] / s,
			m_Value[2] / s
		);
	}

	inline CColor3& operator/= (const T s)
	{
		m_Value[0] /= s;
		m_Value[1] /= s;
		m_Value[2] /= s;
		return *this;
	}

	inline T& operator() (const EColor & c)
	{
		return m_Value[c];
	}

	inline T operator() (const EColor & c) const
	{
		return m_Value[c];
	}

	inline operator T* ()
	{
		return m_Value;
	}

	inline operator const T* () const
	{
		return m_Value;
	}

	CColor3<T> & ToHLS (const T MaxRGB, const T MaxHSV)
	{
		CColor3<T> ColorHSV = GetHLS (MaxRGB, MaxHSV);
	
		m_Value[0] = ColorHSV.m_Value[0];
		m_Value[1] = ColorHSV.m_Value[1];
		m_Value[2] = ColorHSV.m_Value[2];
		return *this;
	}

	// Hue, Saturation, Value => Teinte, Saturation, Valeur)
	CColor3<T> GetHSV (const T MaxRGB, const T MaxHSV)
	{
		CColor3<T> ColorHSV;

		T Max = max(max(m_Value[0], m_Value[1]), m_Value[2]);
		T Min = min(min(m_Value[0], m_Value[1]), m_Value[2]);
		ColorHSV.m_Value[1] = (((Max + Min) * MaxHSV) + MaxRGB) / (2 * MaxRGB);
	
		if (Max == Min) // r=g=b --> achromatic case
		{
			ColorHSV.m_Value[2] = 0; // saturation
			ColorHSV.m_Value[0] = 0; // hue
		}
		else // chromatic case
		{								
			// saturation  
			if (ColorHSV.m_Value[1] <= (MaxHSV / 2))
				ColorHSV.m_Value[2] = (((Max - Min) * MaxHSV) + ((Max + Min) / 2)) / (Max + Min);
			else
				ColorHSV.m_Value[2] = (((Max - Min) * MaxHSV) + ((2 * MaxRGB - Max - Min) / 2)) / (2 * MaxRGB - Max - Min);

			// hue 
			CColor3<T> ColorTmp;
			ColorTmp.m_Value[0] = (((Max - m_Value[0]) * (MaxHSV / 6)) + ((Max - Min) / 2)) / (Max - Min);
			ColorTmp.m_Value[1] = (((Max - m_Value[1]) * (MaxHSV / 6)) + ((Max - Min) / 2)) / (Max - Min);
			ColorTmp.m_Value[2] = (((Max - m_Value[2]) * (MaxHSV / 6)) + ((Max - Min) / 2)) / (Max - Min);

			if (m_Value[0] == Max)
				ColorHSV.m_Value[0] = ColorTmp.m_Value[2] - ColorTmp.m_Value[1];
			else if (m_Value[1] == Max)
				ColorHSV.m_Value[0] = (MaxHSV / 3) + ColorTmp.m_Value[0] - ColorTmp.m_Value[2];
			else // m_Value[2] == Max
				ColorHSV.m_Value[0] = ((2 * MaxHSV) / 3) + ColorTmp.m_Value[1] - ColorTmp.m_Value[0];

			if (ColorHSV.m_Value[0] < 0)
				ColorHSV.m_Value[0] += MaxHSV;
			if (ColorHSV.m_Value[0] > MaxHSV)
				ColorHSV.m_Value[0] -= MaxHSV;
		}
	
		return ColorHSV;
	}
};

template <typename T> CColor3<T> operator* (const T s, const CColor3<T>& c)
{
	return v * c;
}

}; // namespace gtl

#endif //GTL_COLOR_3_H

