//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_quaternion.h
//! \brief Classe CQuaternion, représentant un quaternion.
//////////////////////////////////////////////////////////////////////////////

// v : a vector instance of CVector3<T>
// a : an array instance of T*
// s : a scalar instance of T
// q : a quaternion instance of CQuaternion<T>

#ifndef GTL_QUATERNION_H
#define GTL_QUATERNION_H

#include "gtl_vector3.h"
#include "gtl_matrix3x3.h"
#include "gtl_matrix4x4.h"

namespace gtl {

//! \brief Classe représentant un quaternion.
template <typename T> class CQuaternion
{
private:
	T m_Value[4]; //w, (x, y, z)

public:
	CQuaternion ()
	{
		m_Value[0] = 1;
		m_Value[1] = 0;
		m_Value[2] = 0;
		m_Value[3] = 0;
	}

	CQuaternion (const T w, const T x, const T y, const T z)
	{
		m_Value[0] = w;
		m_Value[1] = x;
		m_Value[2] = y;
		m_Value[3] = z;
	}

    CQuaternion (const T s, const gtl::CVector3<T> v)
	{
		m_Value[0] = s;
		m_Value[1] = v (gtl::X);
        m_Value[2] = v (gtl::Y);
		m_Value[3] = v (gtl::Z);
	}

	CQuaternion (const CQuaternion<T>& q)
	{
		m_Value[0] = q.m_Value[0];
		m_Value[1] = q.m_Value[1];
		m_Value[2] = q.m_Value[2];
		m_Value[3] = q.m_Value[3];
	} 

	CQuaternion (const T a[4])
	{
		m_Value[0] = a[0];
		m_Value[1] = a[1];
		m_Value[2] = a[2];
		m_Value[3] = a[3];
	}

	inline CQuaternion<T> operator* (const CQuaternion<T>& q) const
	{
        CQuaternion<T> Quaternion;
        Quaternion.m_Value[0] = this->m_Value[3] * q.m_Value[0] - this->m_Value[1] * q.m_Value[1] - this->m_Value[2] * q.m_Value[2] - this->m_Value[3] * q.m_Value[3];
        Quaternion.m_Value[1] = this->m_Value[3] * q.m_Value[1] - this->m_Value[1] * q.m_Value[0] - this->m_Value[2] * q.m_Value[3] - this->m_Value[3] * q.m_Value[2];
        Quaternion.m_Value[2] = this->m_Value[3] * q.m_Value[2] - this->m_Value[1] * q.m_Value[3] - this->m_Value[2] * q.m_Value[0] - this->m_Value[3] * q.m_Value[1];
        Quaternion.m_Value[3] = this->m_Value[3] * q.m_Value[3] - this->m_Value[1] * q.m_Value[2] - this->m_Value[2] * q.m_Value[1] - this->m_Value[3] * q.m_Value[0];
        return Quaternion;
	}

	inline CQuaternion& Rotate (T fAngle, T x, T y, T z)
	{
		if ((x != 0 && x != 1) || (y != 0 && y != 1) || (z != 0 && z != 1))
		{
			float fLength = (T) sqrt (x * x + y * y + z * z + m_Value[3]);
			x /= fLength;
			y /= fLength;
			z /= fLength;
		}

		fAngle = (T) DEG_TO_RAD (fAngle);
		float fSin = (T) sin (fAngle / 2.0);

		m_Value[0] = (T) cos (fAngle / 2.0);
        m_Value[1] = x * fSin;
		m_Value[2] = y * fSin;
		m_Value[3] = z * fSin;

		return *this;
	}

    inline CQuaternion& Rotate (T fAngle, CVector3<T> v)
	{
		if ((x != 0 && x != 1) || (y != 0 && y != 1) || (z != 0 && z != 1))
		{
			float fLength = (T) sqrt (v.m_Value[0] * v.m_Value[0] + v.m_Value[1] * v.m_Value[1] + v.m_Value[2] * v.m_Value[2] + m_Value[3]);
			v.m_Value[0] /= fLength;
			v.m_Value[1] /= fLength;
			v.m_Value[2] /= fLength;
		}

		fAngle = (T) DEG_TO_RAD (fAngle);
		float fSin = (T) sin (fAngle / 2.0);

		m_Value[0] = (T) cos (fAngle / 2.0);
        m_Value[1] = v.m_Value[0] * fSin;
		m_Value[2] = v.m_Value[1] * fSin;
		m_Value[3] = v.m_Value[2] * fSin;

		return *this;
	}

    inline CQuaternion& RotateX (T fAngle)
	{
		fAngle = (T) DEG_TO_RAD (fAngle);

		m_Value[0] = (T) cos (fAngle / 2.0);
        m_Value[1] = (T) sin (fAngle / 2.0);
        m_Value[2] = 0;
        m_Value[3] = 0;

		return *this;
	}

    inline CQuaternion& RotateY (T fAngle)
	{
		fAngle = (T) DEG_TO_RAD (fAngle);

		m_Value[0] = (T) cos (fAngle / 2.0);
        m_Value[1] = 0;
		m_Value[2] = (T) sin (fAngle / 2.0);
        m_Value[3] = 0;

		return *this;
	}

    inline CQuaternion& RotateZ (T fAngle)
	{
		fAngle = (T) DEG_TO_RAD (fAngle);

		m_Value[0] = (T) cos (fAngle / 2.0);
        m_Value[1] = 0;
        m_Value[2] = 0;
		m_Value[3] = (T) sin (fAngle / 2.0);

		return *this;
	}

	inline CMatrix4x4<float> GetMatrix ()
	{
		CMatrix4x4<float> Matrix;

		Matrix (gtl::X, gtl::X) = 1.0f - 2.0f * (SQR(m_Value[2]) + SQR(m_Value[3])); 
		Matrix (gtl::Y, gtl::X) = 2.0f * (m_Value[1] * m_Value[2] + m_Value[3] * m_Value[0]);
		Matrix (gtl::Z, gtl::X) = 2.0f * (m_Value[1] * m_Value[3] - m_Value[2] * m_Value[0]);
		Matrix (gtl::W, gtl::X) = 0.0f;  

		Matrix (gtl::X, gtl::Y) = 2.0f * (m_Value[1] * m_Value[2] - m_Value[3] * m_Value[0]);  
		Matrix (gtl::Y, gtl::Y) = 1.0f - 2.0f * (SQR(m_Value[1]) + SQR(m_Value[3])); 
		Matrix (gtl::Z, gtl::Y) = 2.0f * (m_Value[3] * m_Value[2] + m_Value[1] * m_Value[0]);  
		Matrix (gtl::W, gtl::Y) = 0.0f;  

		Matrix (gtl::X, gtl::Z) = 2.0f * (m_Value[1] * m_Value[3] + m_Value[2] * m_Value[0]);
		Matrix (gtl::Y, gtl::Z) = 2.0f * (m_Value[2] * m_Value[3] - m_Value[1] * m_Value[0]);
		Matrix (gtl::Z, gtl::Z) = 1.0f - 2.0f * (SQR(m_Value[1]) + SQR(m_Value[2]));  
		Matrix (gtl::W, gtl::Z) = 0.0f;  

		Matrix (gtl::X, gtl::W) = 0;  
		Matrix (gtl::Y, gtl::W) = 0;  
		Matrix (gtl::Z, gtl::W) = 0;  
		Matrix (gtl::W, gtl::W) = 1.0f;

		return Matrix;
	}

	inline T Magnitude () const
	{
		return (static_cast<T> (sqrt (static_cast<double> (SQR (m_Value[0]) + SQR (m_Value[1]) + SQR (m_Value[2]) + SQR (m_Value[3])))));
	}

	inline CQuaternion<T>& Inverse ()
	{
        return (*this = this->GetInverse ());
	}

	inline CQuaternion<T> GetInverse () const
	{
        CQuaternion<T> q_conj = this->GetConjugate ();
        CQuaternion<T> q_sqr = SQR (q);
		return q_conj / q_sqr;
	}

	inline CQuaternion<T>& Conjugate ()
	{
		m_Value[1] = -m_Value[1];
		m_Value[2] = -m_Value[2];
		m_Value[3] = -m_Value[3];
	}

	inline CQuaternion<T> GetConjugate () const
	{
		return CQuaternion<T> (m_Value[0], -m_Value[1], -m_Value[2], -m_Value[3]);
	}

	inline CQuaternion<T>& Indentity ()
	{
		m_Value[0] = 1;
        m_Value[1] = 0;
		m_Value[2] = 0;
		m_Value[3] = 0;
	}

	inline CQuaternion<T> GetIndentity () const
	{
		return CQuaternion<T> (1, 0, 0, 0);
	}

	inline CQuaternion<T>& Negation ()
	{
		m_Value[0] = -m_Value[0];
		m_Value[1] = -m_Value[1];
		m_Value[2] = -m_Value[2];
		m_Value[3] = -m_Value[3];
	}

	inline CQuaternion<T> GetNegation () const
	{
		return CQuaternion<T> (-m_Value[0], -m_Value[1], -m_Value[2], -m_Value[3]);
	}

	inline CQuaternion<T> operator- () const
	{
		return GetNegation ();
	}
};

}; // namespace gtl

#endif //GTL_QUATERNION_H

