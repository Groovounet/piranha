//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_color4.h
//! \brief Classe CColor4, pour les couleurs RGBA.
//////////////////////////////////////////////////////////////////////////////

#ifndef GTL_COLOR_4_H
#define GTL_COLOR_4_H

#include "gtl_color.h"

namespace gtl {

#define GTL_COLOR_4_RANG 4

//! \brief Classe pour l'utilisable de couleurs RGBA.
template <typename T> class CColor4
{
private:
	T m_Value[GTL_COLOR_4_RANG];

public:
	CColor4 ()
	{
		m_Value[0] = 0;
		m_Value[1] = 0;
		m_Value[2] = 0;
		m_Value[3] = 0;
	}

	CColor4 (const T x, const T y, const T z, const T w)
	{
		m_Value[0] = x;
		m_Value[1] = y;
		m_Value[2] = z;
		m_Value[3] = w;
	}

	CColor4 (const CColor4<T> & c)
	{
		m_Value[0] = c.m_Value[0];
		m_Value[1] = c.m_Value[1];
		m_Value[2] = c.m_Value[2];
		m_Value[3] = c.m_Value[3];
	} 

	CColor4 (unsigned int uiColor)
	{
		m_Value[0] = (uiColor & 0x000000ff);
		m_Value[1] = (uiColor & 0x0000ff00) >> 8;
		m_Value[2] = (uiColor & 0x00ff0000) >> 16;
	}

	CColor4 (const T a[GTL_COLOR_4_RANG])
	{
		m_Value[0] = a[0];
		m_Value[1] = a[1];
		m_Value[2] = a[2];
		m_Value[3] = a[3];
	}

	inline const bool operator== (const CColor4<T> & c) const
	{
		return (m_Value[0] == c.m_Value[0] 
			&&	m_Value[1] == c.m_Value[1] 
			&&	m_Value[2] == c.m_Value[2] 
			&&	m_Value[3] == c.m_Value[3]);
	}

	inline const bool operator!= (const CColor4<T> & c) const
	{
		return !(*this==v);
	}

	inline CColor4 operator= (const CColor4<T> & c)
	{
		m_Value[0] = c.m_Value[0];
		m_Value[1] = c.m_Value[1];
		m_Value[2] = c.m_Value[2];
		m_Value[3] = c.m_Value[3];
		return *this;
	}

	inline CColor4 operator= (const T a[GTL_COLOR_4_RANG])
	{
		m_Value[0] = a[0];
		m_Value[1] = a[1];
		m_Value[2] = a[2];
		m_Value[3] = a[3];
		return *this;
	}

	inline CColor4 operator+ (const CColor4<T>& c) const
	{
		return CColor4<T> (
			m_Value[0] + c.m_Value[0], 
			m_Value[1] + c.m_Value[1], 
			m_Value[2] + c.m_Value[2], 
			m_Value[3] + c.m_Value[3]
		);
	}

	inline CColor4& operator+= (const CColor4<T> & c)
	{
		m_Value[0] += c.m_Value[0];
		m_Value[1] += c.m_Value[1];
		m_Value[2] += c.m_Value[2];
		m_Value[3] += c.m_Value[3];
	}

	inline CColor4 operator- (const CColor4<T> & c) const
	{
		return CColor4<T> (
			m_Value[0] - c.m_Value[0],
			m_Value[1] - c.m_Value[1],
			m_Value[2] - c.m_Value[2],
			m_Value[3] - c.m_Value[3]
		);
	}

	inline CColor4 operator-= (const CColor4<T> & c)
	{
		m_Value[0] -= c.m_Value[0];
		m_Value[1] -= c.m_Value[1];
		m_Value[2] -= c.m_Value[2];
		m_Value[3] -= c.m_Value[3];
	}

	inline CColor4 operator* (const T s) const
	{
		return CColor4<T> (
			m_Value[0] * s,
			m_Value[1] * s,
			m_Value[2] * s,
			m_Value[3] * s
		);
	}

	inline CColor4 operator*= (const T s)
	{
		m_Value[0] *= s;
		m_Value[1] *= s;
		m_Value[2] *= s;
		m_Value[3] *= s;
	}

	inline CColor4 operator/ (const T s) const
	{
		return CColor4<T> (
			m_Value[0] / s,
			m_Value[1] / s,
			m_Value[2] / s,
			m_Value[3] / s
		);
	}

	inline CColor4 operator/= (const T s)
	{
		m_Value[0] /= s;
		m_Value[1] /= s;
		m_Value[2] /= s;
		m_Value[3] /= s;
		return *this;
	}

	inline T& operator() (const EColor & Coord)
	{
		return m_Value[Coord];
	}

	inline T operator() (const EColor & Coord) const
	{
		return m_Value[Coord];
	}

	inline operator T* ()
	{
		return m_Value;
	}

	inline operator const T* () const
	{
		return m_Value;
	}

	CColor4<T> & ToHLS (const T MaxRGB, const T MaxHLS)
	{
		CColor4<T> ColorHSV = GetHLS (MaxRGB, MaxHLS);

		m_Value[0] = ColorHSV.m_Value[0];
		m_Value[1] = ColorHSV.m_Value[1];
		m_Value[2] = ColorHSV.m_Value[2];
		return *this;
	}

	CColor4<T> GetHSV (const T MaxRGB, const T MaxHLS)
	{
		CColor4<T> ColorHSV;

		T Max = max(max(m_Value[0], m_Value[1]), m_Value[2]);
		T Min = min(min(m_Value[0], m_Value[1]), m_Value[2]);
		ColorHSV.m_Value[1] = (((Max + Min) * MaxHLS) + MaxRGB) / (2 * MaxRGB);
	
		if (Max == Min) // r=g=b --> achromatic case
		{
			ColorHSV.m_Value[2] = 0; // saturation
			ColorHSV.m_Value[0] = 0; // hue
		}
		else // chromatic case
		{								
			// saturation  
			if (ColorHSV.m_Value[1] <= (MaxHLS / 2))
				ColorHSV.m_Value[2] = (((Max - Min) * MaxHLS) + ((Max + Min) / 2)) / (Max + Min);
			else
				ColorHSV.m_Value[2] = (((Max - Min) * MaxHLS) + ((2 * MaxRGB - Max - Min) / 2)) / (2 * MaxRGB - Max - Min);

			// hue 
			CColor4<T> ColorTmp;
			ColorTmp.m_Value[0] = (((Max - m_Value[0]) * (MaxHLS / 6)) + ((Max - Min) / 2)) / (Max - Min);
			ColorTmp.m_Value[1] = (((Max - m_Value[1]) * (MaxHLS / 6)) + ((Max - Min) / 2)) / (Max - Min);
			ColorTmp.m_Value[2] = (((Max - m_Value[2]) * (MaxHLS / 6)) + ((Max - Min) / 2)) / (Max - Min);

			if (m_Value[0] == Max)
				ColorHSV.m_Value[0] = ColorTmp.m_Value[2] - ColorTmp.m_Value[1];
			else if (m_Value[1] == Max)
				ColorHSV.m_Value[0] = (MaxHLS / 3) + ColorTmp.m_Value[0] - ColorTmp.m_Value[2];
			else // m_Value[2] == Max
				ColorHSV.m_Value[0] = ((2 * MaxHLS) / 3) + ColorTmp.m_Value[1] - ColorTmp.m_Value[0];

			if (ColorHSV.m_Value[0] < 0)
				ColorHSV.m_Value[0] += MaxHLS;
			if (ColorHSV.m_Value[0] > MaxHLS)
				ColorHSV.m_Value[0] -= MaxHLS;
		}
	
		ColorHSV.m_Value[3] = m_Value[3];
		return ColorHSV;
	}
};

template <typename T> CColor4<T> operator* (const T s, const CColor4<T>& c)
{
	return c * nb;
}

}; // namespace gtl

#endif //GTL_COLOR_4_H
