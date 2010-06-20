//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_color.h
//! \brief Outils commun aux classes couleurs
//////////////////////////////////////////////////////////////////////////////

#ifndef GTL_COLOR_H
#define GTL_COLOR_H

namespace gtl {

//! \brief Paramètres permettant l'accès aux composantes des couleurs.
typedef enum
{
	R = 0,
	G = 1,
	B = 2,
	A = 3,
	H = 0,
	L = 1,
	S = 2
} EColor;

}; // namespace gtl

#endif //GTL_COLOR_H
