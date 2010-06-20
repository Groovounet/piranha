/***********************************************\
	GTL sample
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	particle_system.cpp, 06/10/2004
\***********************************************/

#include "./particle_system.h"
#include "./sample.h"

CParticleSystem::CParticleSystem ()
{
	m_Position = gtl::CVector3<float>(128, 128, 128);
	m_TimerCreate.Init ();
	for (int i = 0; i < PARTICLE_MAX; i++)
		m_pElements[i] = 0;
}

CParticleSystem::~CParticleSystem ()
{
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_pElements[i])
			delete m_pElements[i];
	}
}

// Recherche d'un index libre dans la table des particules
int CParticleSystem::_FreeIndex () const
{
	for (int i = 0; i < PARTICLE_MAX; i++)
		if (!m_pElements[i])
			return i;
	return -1;
}

void CParticleSystem::Update ()
{
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_pElements[i])
		{
			// 07/05/2004 - Particles delete
			if (m_pElements[i]->IsEnd ())
			{
				delete m_pElements[i];
				m_pElements[i] = 0;
				continue;
			}

			if (m_pElements[i]->Position () (gtl::Z) < (g_pTerrain->Height (m_pElements[i]->Position ()) + PARTICLE_SIZE * 3 / 4))
			{
				m_pElements[i]->m_Position = m_pElements[i]->Position ();
				gtl::CVector3<float> Normal = g_pTerrain->Normal (m_pElements[i]->Position ());
				// 18/10/2004 - Les deux lignes suivantes offrent un résultat identique mais la seconde est plus rapide.
				//m_pElements[i]->m_Speed = -m_pElements[i]->Speed ().GetProj (Normal) + m_pElements[i]->Speed ().GetPerp (Normal);
				m_pElements[i]->m_Speed = m_pElements[i]->Speed () - 2 * (m_pElements[i]->Speed ().GetDot (Normal)) * Normal;
				m_pElements[i]->m_TimeMove.Init ();
			}
		}
	}

	// Si le temps entre 2 créations de particules est écoulé
	if (m_TimerCreate.GetTime () > 0.1f)
	{
		m_TimerCreate.Init ();
		// S'il existe un index libre
		int iIndex = _FreeIndex ();
		if (iIndex != -1)
			m_pElements[iIndex] = new CParticleElement (
				m_Position, 
				PARTICLE_TIME);
	}
}

void CParticleSystem::Draw () const
{
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_POINT_SPRITE_ARB);
	glEnable (GL_BLEND);
	glEnable (GL_CULL_FACE);
	glDepthMask (0);

	glTexEnvf (GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);

	glBindTexture (GL_TEXTURE_2D, m_uiTexture);
	glPointSize (PARTICLE_SIZE);
	glBegin (GL_POINTS);
    for (unsigned int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_pElements[i])
		{
			glColor4fv (m_pElements[i]->Color ());
			glVertex3fv (m_pElements[i]->Position ());
		}
	}
	glEnd ();

	glDepthMask (1);
	glDisable (GL_CULL_FACE);
	glDisable (GL_BLEND);
	glDisable (GL_POINT_SPRITE_ARB);
	glDisable (GL_TEXTURE_2D);
}

bool CParticleSystem::Load (const char* szTexture)
{
	gtl::CImageTGA Texture (szTexture);
	if (!Texture.IsLoaded ())
		return false;

	glGenTextures (1, &m_uiTexture);
	glBindTexture (GL_TEXTURE_2D, m_uiTexture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, 3, Texture.Width (), Texture.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Texture.Data ());

	return true;
}
