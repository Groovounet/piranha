//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 02/06/2004
//! \file gtl_polynomial.h
//! \brief Classe CPolynomial, représentant un polynome.
//////////////////////////////////////////////////////////////////////////////

#ifndef GTL_POLYNOMIAL_H
#define GTL_POLYNOMIAL_H

namespace gtl {

//! \brief Classe représentant un polynome.
class CPolynomial
{
private:
	short m_iDegree;
	short m_iMaxDegree;
	double* m_pfTerm;

	void Scale (double fOldUnits, double fNewUnits);

public:
	CPolynomial (unsigned short unDegree = 0);
	CPolynomial (const CPolynomial & Polynomial);
	~CPolynomial ();

	//! Groove - 22/10/2003 - Load the polygone classe with 2 arrays and a Lagrange serie build.
	void Load (unsigned int uiArraySize, double* x, double* y);
	//! Groove - 19/11/2003 - Load the polygone classe using termes
	void Load (unsigned int uiDegree, double* t);

	bool IsNull ();
	//! Groove - 22/10/2003 - Evalute le polynomial function with the value of x
	double operator() (double x);

	CPolynomial& operator= (const CPolynomial & Polynomial);
	
	CPolynomial operator- () const;

	CPolynomial operator+ (const CPolynomial & Polynomial) const;
	CPolynomial& operator+= (const CPolynomial & Polynomial);

	CPolynomial operator- (const CPolynomial & Polynomial) const;
	CPolynomial& operator-= (const CPolynomial & Polynomial);
	
	//CPolynomial operator* (const CPolynomial & Polynomial) const;
	//CPolynomial& operator*= (const CPolynomial & Polynomial);

	//CPolynomial operator+ (double s) const;
	//CPolynomial& operator+= (double s);

	//CPolynomial operator- (double s) const;
	//CPolynomial& operator-= (double s);

	CPolynomial operator* (double s) const;
	CPolynomial& operator*= (double s);

	CPolynomial operator/ (double s) const;
	CPolynomial& operator/= (double s);

	void Add (const CPolynomial & Polynomial, double coeff = 1);

	void SetDegree (int uiDegree);
	void SetTerm (int coeff, double value);

	int GetDegree () const;
	double GetTerm (int coeff) const;

	CPolynomial GetDerivative () const;
	CPolynomial GetCompress (double fEpsilon) const;
};

}; // namespace gtl

#endif //GTL_POLYNOMIAL_H
