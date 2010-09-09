//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_polynomial.cpp
//! \brief Classe CPolynomial, représentant un polynome.
//////////////////////////////////////////////////////////////////////////////

#include "gtl_polynomial.h"
#include <cmath>

namespace gtl {

CPolynomial::CPolynomial (unsigned short unDegree)
{
   m_iDegree = unDegree;
   m_iMaxDegree = unDegree;
   m_pfTerm = new double [unDegree + 1];
}

CPolynomial::CPolynomial (const CPolynomial & Polynomial)
{
    m_iDegree = Polynomial.m_iMaxDegree;
    m_pfTerm = new double [m_iMaxDegree+1];
    for (int i = 0; i <= m_iDegree; i++)
        m_pfTerm[i] = Polynomial.m_pfTerm[i];
}

CPolynomial::~CPolynomial ()
{
   delete [] m_pfTerm;
}

double CPolynomial::operator() (double x)
{
    double   fPow = 1;
    double   fSum = 0;

    for (int i = 0; i <= m_iDegree; i++)
    {
        fSum += fPow * m_pfTerm[i];
        fPow *= x;
    }

    return fSum;
}
/*
double CPolynomial::Evalutate (double x, unsigned int uiDegree)
{
	double   fPow = 1;
	double   fSum = 0;

	for (unsigned int i = uiDegree; i <= m_iDegree; i++)
	{
		fSum += fPow * m_pfTerm[i];
		fPow *= x;
	}

	return fSum;
}
*/
void CPolynomial::Scale (double fOldUnits, double fNewUnits)
{
	double fMult = fNewUnits / fOldUnits;

	for (int i = 0; i <= m_iDegree; ++i)
		m_pfTerm[i] *= fMult;
}

bool CPolynomial::IsNull ()
{
	return ((m_iDegree == 0) && (m_pfTerm[0] == 0));
}

void CPolynomial::Load (unsigned int uiArraySize, double* x, double* y)
{
	SetDegree(0);
	m_pfTerm[0] = 0;

	for (unsigned int j = 0; j < uiArraySize; j++)
	{
		CPolynomial Polynomial (1);
		Polynomial.m_pfTerm[0] = 1;

		for (unsigned int i = 0; i < uiArraySize; i++)
			if (i != j)
				Polynomial *= -x[i];

		Polynomial.Scale (Polynomial (x[j]), y[j]);
		Add (Polynomial);
	}
}

CPolynomial& CPolynomial::operator= (const CPolynomial & Polynomial)
{
	if (m_pfTerm)
		delete[] m_pfTerm;
	m_iDegree = Polynomial.m_iDegree;

	if (m_iDegree >= 0)
	{
		m_pfTerm = new double [m_iDegree+1];
		for (int i = 0; i <= m_iDegree; i++)
			m_pfTerm[i] = Polynomial.m_pfTerm[i];
	}
	return *this;
}

CPolynomial CPolynomial::operator- () const
{
	CPolynomial Polynomial (m_iMaxDegree);
	for (int i = 0; i < m_iMaxDegree; i++)
		Polynomial.m_pfTerm[i] = -m_pfTerm[i];
	return Polynomial;
}

CPolynomial CPolynomial::operator+ (const CPolynomial & Polynomial) const
{
	CPolynomial PolynomialReturned;

	if (Polynomial.m_iDegree > m_iDegree)
		PolynomialReturned.SetDegree (Polynomial.m_iDegree);
	else
		PolynomialReturned.SetDegree (m_iDegree);

	for (int i = 0; i <= PolynomialReturned.m_iDegree; i++)
		PolynomialReturned.SetTerm (	i, m_pfTerm[i] + Polynomial.GetTerm (i));

	return PolynomialReturned;
}

CPolynomial& CPolynomial::operator+= (const CPolynomial & Polynomial)
{
	if (Polynomial.m_iDegree > m_iDegree)
		SetDegree (Polynomial.m_iDegree);

	for (int i = 0; i <= m_iDegree; i++)
		m_pfTerm[i] += Polynomial.m_pfTerm[i];

	return *this;
}

CPolynomial CPolynomial::operator* (double s) const
{
	CPolynomial Polynomial;
	Polynomial.SetDegree (m_iDegree + 1);

	for (int i = m_iDegree; i > 0; --i)
		Polynomial.m_pfTerm[i] = m_pfTerm[i-1] + m_pfTerm[i] * s;

	Polynomial.m_pfTerm[0] = m_pfTerm[0] * s;
	return Polynomial;
}

CPolynomial& CPolynomial::operator*= (double s)
{
	SetDegree (m_iDegree + 1);

	for (int i = m_iDegree; i > 0; --i)
		m_pfTerm[i] = m_pfTerm[i-1] + m_pfTerm[i] * s;

	m_pfTerm[0] = m_pfTerm[0] * s;
	return *this;
}

void CPolynomial::Add (const CPolynomial & Polynomial, double fCoeff)
{
	if (Polynomial.m_iDegree > m_iDegree)
		SetDegree (Polynomial.m_iDegree);

	for (int i = 0; i <= m_iDegree; i++)
		m_pfTerm[i] += fCoeff * Polynomial.m_pfTerm[i];
}

void CPolynomial::SetDegree (int iDegree)
{
	int i;

	if (iDegree > m_iMaxDegree)
	{
		double* pfTerm = new double[iDegree + 1];

		for (i = 0; i <= iDegree; ++i)
			pfTerm[i] = m_pfTerm[i];

		for (; i <= iDegree; ++i)
			pfTerm[i] = 0;

		delete [] m_pfTerm;
		m_pfTerm = pfTerm;
		m_iMaxDegree = iDegree;
	}
	else if (iDegree > m_iDegree)
	{
		for (i = m_iDegree + 1; i <= iDegree; ++i)
			m_pfTerm[i] = 0;
	}

	m_iDegree = iDegree;

	return;
}

void CPolynomial::SetTerm (int iCoeff, double fValue)
{
	if (iCoeff > m_iDegree)
		SetDegree(iCoeff);

	m_pfTerm[iCoeff] = fValue;
}

int CPolynomial::GetDegree () const
{
	return m_iDegree;
}

double CPolynomial::GetTerm (int iCoeff) const
{
	if ((iCoeff >= 0) && (iCoeff <= m_iDegree))
		return m_pfTerm[iCoeff];

	return 0;
}

CPolynomial CPolynomial::GetDerivative () const
{
	if (m_iDegree > 0)
	{
		CPolynomial Polynomial (m_iDegree-1);
		for (int i = 0, j = 1; i < m_iDegree; i++, j++)
			Polynomial.m_pfTerm[i] = j * m_pfTerm[j];
		return Polynomial;
	}
	else if (m_iDegree == 0)
	{
		CPolynomial Polynomial (0);
		Polynomial.m_pfTerm[0] = 0.0;
		return Polynomial;
	}
	return CPolynomial ();
}

CPolynomial CPolynomial::GetCompress (double fEpsilon) const
{
	CPolynomial Polynomial;
	Polynomial = *this;

	int i;
	for (i = Polynomial.m_iDegree; i >= 0; i--)
	{
		if (fabs (Polynomial.m_pfTerm[i]) <= fEpsilon)
			Polynomial.m_iDegree--;
		else
			break;
	}

	if (Polynomial.m_iDegree >= 0)
	{
		double fInv = 1.0 / Polynomial.m_pfTerm[Polynomial.m_iDegree];
		Polynomial.m_pfTerm[Polynomial.m_iDegree] = 1.0;
		for (i = 0; i < Polynomial.m_iDegree; i++)
			Polynomial.m_pfTerm[i] *= fInv;
	}

	return Polynomial;
}

}; // namespace gtl
