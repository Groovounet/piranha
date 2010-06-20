//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-14-2004
//! \file ./window/window.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./window.h"
#include "../util/timer_global.h"

using namespace window;

unsigned short CWindow::m_unHeight;
unsigned short CWindow::m_unWidth;

CWindow::CWindow ()
{
	m_bExit = false;
	m_szName = std::string ("Window");
	m_unWidth = 640;
	m_unHeight = 480;
	m_ucColor = 32;
	m_ucFFSA = 1;
	m_ucDepth = 16;
	m_ucStencil = 0;
	m_uiViewDistance = 256;
	m_uiOption = 0;
	m_fSync = 1.f / SYNC_DEFAULT;
    m_TimerSync.Init ();
}

CWindow::~CWindow ()
{

}

unsigned short CWindow::Height ()// const
{
	return m_unHeight;
}

unsigned short CWindow::Width ()// const
{
	return m_unWidth;
}

void CWindow::Enable (const EOption & Option)
{
	m_uiOption |= Option;
}

void CWindow::Disable (const EOption & Option)
{
	m_uiOption &= ~Option;
}

void CWindow::Config (const EConfig & Config, int iValue)
{
	switch (Config)
	{
	default:
		break;
	case CONFIG_HEIGHT:
		m_unHeight = iValue;
		break;
	case CONFIG_WIDTH:
		m_unWidth = iValue;
		break;
	case CONFIG_COLOR:
		m_ucColor = iValue;
		break;
	case CONFIG_FFSA:
		m_ucFFSA = iValue;
		break;
	case CONFIG_DEPTH:
		m_ucDepth = iValue;
		break;
	case CONFIG_STENCIL:
		m_ucStencil = iValue;
		break;
	case CONFIG_VIEW_DISTANCE:
		m_uiViewDistance = iValue;
		break;
	case CONFIG_SYNC:
		m_fSync = 1.f / iValue;
		break;
	}
}

