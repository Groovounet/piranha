//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004, Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 19/09/2004
//! \file gtl_rand.h
//! \brief Classe CRand, pour la recherche de nombre aléatoire.
//////////////////////////////////////////////////////////////////////////////

#ifndef GTL_RAND_H
#define GTL_RAND_H

#include "gtl_math.h"
#include <cstdlib>
#include <ctime>

namespace gtl {

//! \brief Classe permettant la recherche de nombre aléatoire.
class CRand
{
public:
	static void Init (long iStart = clock ());
	//! Retourne un nombre flottant entre 0 et 1
	static float Float ();
	//! Retourne un nombre flottant entre 0 et fMax
	static float Float (float fMax);
	//! Retourne un nombre flottant entre fMin et fMax
	static float Float (float fMin, float fMax);
	//! Retourne un nombre entier entre 0 et iMax
	static long Int (long iMax);
	//! Retourne un nombre entier entre iMin et iMax
	static long Int (long iMin, long iMax);
};

}; // namespace gtl

#endif //GTL_RAND_H
