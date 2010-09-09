//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 19/09/2004
//! \file gtl_rand.cpp
//! \brief Classe CRand, pour la recherche de nombre aléatoire.
//////////////////////////////////////////////////////////////////////////////

#include "gtl_rand.h"

namespace gtl {

void CRand::Init (long iStart)
{
	srand (iStart);
}

float CRand::Float ()
{
	return rand () / ((float) RAND_MAX);
}

float CRand::Float (float fMax)
{
	return Float () * fMax;
}

float CRand::Float (float fMin, float fMax)
{
	return (Float () * (fMax - fMin)) + fMin;
}

long CRand::Int (long iMax)
{
	return (long) ((float) rand () / RAND_MAX * iMax);
}

long CRand::Int (long iMin, long iMax)
{
	return (long) (((float) rand () / RAND_MAX * (iMax - iMin )) + iMin);
}

}; // namespace gtl
