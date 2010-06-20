//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 03/10/2004
//! \file gtl_math.h
//! \brief Outils mathématiques.
//////////////////////////////////////////////////////////////////////////////

#ifndef GTL_MATH_H
#define GTL_MATH_H

#include <math.h>

namespace gtl {

#define PI 3.1415926535
#define PI_OVER_180 0.0174532925
#define PI_UNDER_180 57.295779513
#define DEG_TO_RAD(angle) (angle * PI_OVER_180)
#define RAD_TO_DEG(angle) (angle * PI_UNDER_180)
#define SQR(x) ((x)*(x))

#ifndef MAX
#define MAX(a,b)       ((a)>(b)?(a):(b))
#endif
#ifndef MAX3
#define MAX3(a,b,c)    MAX(MAX(a,b),MAX(b,c))
#endif
#ifndef MAX4
#define MAX4(a,b,c,d)  MAX(MAX(a,b),MAX(b,c),MAX(c,a))
#endif
#ifndef MIN
#define MIN(a,b)       ((a)<(b)?(a):(b))
#endif
#ifndef MIN3
#define MIN3(a,b,c)    MIN(MIN(a,b),MIN(b,c))
#endif
#ifndef MIN4
#define MIN4(a,b,c,d)  MIN(MIN(a,b),MIN(b,c),MIN(c,a))
#endif

//! \brief Classe contenant des outils mathématiques.
template <typename T = int> class CMath
{
public:
	inline bool Max (T x, T y)
	{
		return x > y ? x : y;
	}

	inline bool Min (T x, T y)
	{
		return x < y ? x : y;
	}

	inline bool Max (T a, T b, T c, T d)
	{
        T Max1 = (a > b ? a : b);
        T Max2 = (c > d ? c : d);
        return (Max1 > Max2 ? Max1 : Max2);
	}

	inline bool Min (T a, T b, T c, T d)
	{
        T Min1 = (a < b ? a : b);
        T Min2 = (c < d ? c : d);
        return (Min1 < Min2 ? Min1 : Min2);
	}

	static T DegToRad (T deg)
	{
		return static_cast<T> (deg * PI_OVER_180);
	}

	static T RadToDeg (T rad)
	{
		return static_cast<T> (rad * PI_UNDER_180);
	}
/*
	inline static unsigned long Factorial (const unsigned long n)
	{
		unsigned long f = 1, i;
		for (i = 1; i <= n; i++)
			f *= i;
		return f;
	}
*/
/*
	static T BitInversion (T Nb)
	{
		T NbBuffer = 0;
		for (short i = 0; i < sizeof(T); i++)
			if (Nb & (1<<i))
				NbBuffer |= (1<<(31-i));
		return NbBuffer;
	}
*/
	static T Sqr (const T & nb) {return nb * nb;}
};

}; // namespace gtl

#endif //GTL_MATH_H






















