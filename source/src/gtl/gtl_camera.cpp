//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_camera.cpp
//! \brief Classe CCamera, pour la visualisation d'une scène.
//////////////////////////////////////////////////////////////////////////////

#include "gtl_camera.h"
#include "gtl_math.h"
#include "gtl_gl.h"
#include <cmath>

namespace gtl {

CCamera::CCamera ()
{
	m_Position = gtl::CVector3<float> (0.0, 0.0, 0.0);
	m_View = gtl::CVector3<float> (0.0, 1.0, 0.0);
	m_UpVector = gtl::CVector3<float> (0.0, 0.0, 1.0);
	m_fViewDistance = 1.0f;
	m_fCurrentRotX = 0.0f;
}

CCamera::~CCamera ()
{

}

void CCamera::Enable (unsigned int uiOption)
{
	m_uiOption |= uiOption;
}

void CCamera::Disable (unsigned int uiOption)
{
	m_uiOption &= ~uiOption;
}

void CCamera::Init (const CVector3<float> & Position, const CVector3<float> & View)
{
    m_Position = Position;
    m_View = View;
}

void CCamera::LookAt (float fMoveZ, float fMoveX)
{
	UpdateView (fMoveZ / 10.f, fMoveX / 10.f);

	gluLookAt (
		m_Position (X), m_Position (Y), m_Position (Z),
		m_View (X), m_View (Y), m_View (Z),
		m_UpVector (X), m_UpVector (Y), m_UpVector (Z)
	);

	if (m_uiOption & CAMERA_FRUSTUM)
		CalculatePlanes ();
}

void CCamera::LookAt (const CVector3<float> & View)
{
	m_View = m_Position + View;

	gluLookAt (
		m_Position (X), m_Position (Y), m_Position (Z),
		m_View (X), m_View (Y), m_View (Z),
		m_UpVector (X), m_UpVector (Y), m_UpVector (Z)
	);

	if (m_uiOption & CAMERA_FRUSTUM)
		CalculatePlanes ();
}

void CCamera::LookAt (const CVector3<float> & Position, const CVector3<float> & View)
{
	gluLookAt (
		Position (X), Position (Y), Position (Z),
		View (X), View (Y), View (Z),
		m_UpVector (X), m_UpVector (Y), m_UpVector (Z)
	);

	if (m_uiOption & CAMERA_FRUSTUM)
		CalculatePlanes ();
}

void CCamera::LookAt ()
{
	gluLookAt (
		m_Position (X), m_Position (Y), m_Position (Z),
		m_View (X), m_View (Y), m_View (Z),
		m_UpVector (X), m_UpVector (Y), m_UpVector (Z)
	);
}

void CCamera::Position (const CVector3<float> & Position, float fMoveZ, float fMoveX)
{
	//CVector3<float> l_Position = Position;

	Move (Position (X));
	Strafe (Position (Y));
	MoveUp (Position (Z));

	UpdateView (fMoveZ, fMoveX);
}

void CCamera::UpdateView (float fMoveZ, float fMoveX)
{
	if ((fMoveX == 0) && (fMoveZ == 0))
		return;

	float fAngleX = CMath<float>::DegToRad(fMoveX);
	float fAngleZ = CMath<float>::DegToRad(fMoveZ);

	m_fCurrentRotX += fAngleX;
	if (!(m_uiOption & CAMERA_TURN_OVER))
	{
		if (m_fCurrentRotX > PI / 2)
		{
			m_fCurrentRotX = static_cast<float>(PI / 2);
			return;
		}
		if (m_fCurrentRotX < - (PI / 2))
		{
			m_fCurrentRotX = static_cast<float>(- PI / 2);
			return;
		}
	}

	CVector3<float> Axis = ((m_View - m_Position) ^ m_UpVector).GetNormalize ();

	RotateView (fAngleX, Axis);
	RotateView (fAngleZ, m_UpVector);
}

void CCamera::RotateView (float fAngle, const CVector3<float> & Axis)
{
	CVector3<float> NewView;
	CVector3<float> View = m_View - m_Position;

	float fCosTheta = cos (fAngle);
	float fSinTheta = sin (fAngle);

	NewView (X)  = (fCosTheta + (1 - fCosTheta) * Axis(X) * Axis(X)) * View (X);
	NewView (X) += ((1 - fCosTheta) * Axis(X) * Axis(Y) - Axis(Z) * fSinTheta) * View (Y);
	NewView (X) += ((1 - fCosTheta) * Axis(X) * Axis(Z) + Axis(Y) * fSinTheta) * View (Z);

	NewView (Y)  = ((1 - fCosTheta) * Axis(X) * Axis(Y) + Axis(Z) * fSinTheta) * View (X);
	NewView (Y) += (fCosTheta + (1 - fCosTheta) * Axis(Y) * Axis(Y)) * View (Y);
	NewView (Y) += ((1 - fCosTheta) * Axis(Y) * Axis(Z) - Axis(X) * fSinTheta) * View (Z);

	NewView (Z)  = ((1 - fCosTheta) * Axis(X) * Axis(Z) - Axis(Y) * fSinTheta) * View (X);
	NewView (Z) += ((1 - fCosTheta) * Axis(Y) * Axis(Z) + Axis(X) * fSinTheta) * View (Y);
	NewView (Z) += (fCosTheta + (1 - fCosTheta) * Axis(Z) * Axis(Z)) * View (Z);

	m_View = m_Position + NewView;
}

void CCamera::Move (float fSpeed)
{
	CVector3<float> Vector = m_View - m_Position;

	m_Position += Vector * fSpeed;
	m_View += Vector * fSpeed;
}

void CCamera::Strafe (float fSpeed)
{
	CVector3<float> Vector = (m_View - m_Position) ^ m_UpVector;

	m_Position += Vector * fSpeed;
	m_View += Vector * fSpeed;
}

void CCamera::MoveUp (float fSpeed)
{
	CVector3<float> Vector = m_UpVector;

	m_Position += Vector * fSpeed;
	m_View += Vector * fSpeed;
}

float CCamera::GetDistance (float x, float y, float z)
{
	return CMath<float>::Sqr (m_Position (X) - x) + CMath<float>::Sqr (m_Position (Y) - y) + CMath<float>::Sqr (m_Position (Z) - z);
}

float CCamera::GetDistance (float *fCoord)
{
	return CMath<float>::Sqr (m_Position (X) - fCoord[0]) + CMath<float>::Sqr (m_Position (Y) - fCoord[1]) + CMath<float>::Sqr (m_Position (Z) - fCoord[2]);
}

bool CCamera::TestDistance (float x, float y, float z)
{
	if ((CMath<float>::Sqr (m_Position (X) - x) + CMath<float>::Sqr (m_Position (Y) - y) + CMath<float>::Sqr (m_Position (Z) - z)) > CMath<float>::Sqr (m_fViewDistance))
		return false;
	return true;
}

bool CCamera::IsInFrustum (float x, float y, float z, float fRadius)
{
	for (int i=0; i<6; i++)
	{
		if (m_fPlanes[i][0] * x +
			m_fPlanes[i][1] * y +
			m_fPlanes[i][2] * z +
			m_fPlanes[i][3] <= -fRadius)
			return false;
	}

	return true;
}

bool CCamera::IsInFrustum (float *fCoord, float fRadius)
{
	for (int i=0; i<6; i++)
	{
		if (m_fPlanes[i][0] * fCoord[0] +
			m_fPlanes[i][1] * fCoord[1] +
			m_fPlanes[i][2] * fCoord[2] +
			m_fPlanes[i][3] <= -fRadius)
			return false;
	}

	return true;
}

void CCamera::CalculatePlanes ()
{
	float p[16];	// projection matrix
	float v[16];	// model-view matrix
	float mvp[16];	// model-view-projection matrix
	float fDist;

	glGetFloatv (GL_PROJECTION_MATRIX, p);
	glGetFloatv (GL_MODELVIEW_MATRIX, v);

	mvp[ 0] = v[ 0] * p[ 0] + v[ 1] * p[ 4] + v[ 2] * p[ 8] + v[ 3] * p[12];
	mvp[ 1] = v[ 0] * p[ 1] + v[ 1] * p[ 5] + v[ 2] * p[ 9] + v[ 3] * p[13];
	mvp[ 2] = v[ 0] * p[ 2] + v[ 1] * p[ 6] + v[ 2] * p[10] + v[ 3] * p[14];
	mvp[ 3] = v[ 0] * p[ 3] + v[ 1] * p[ 7] + v[ 2] * p[11] + v[ 3] * p[15];

	mvp[ 4] = v[ 4] * p[ 0] + v[ 5] * p[ 4] + v[ 6] * p[ 8] + v[ 7] * p[12];
	mvp[ 5] = v[ 4] * p[ 1] + v[ 5] * p[ 5] + v[ 6] * p[ 9] + v[ 7] * p[13];
	mvp[ 6] = v[ 4] * p[ 2] + v[ 5] * p[ 6] + v[ 6] * p[10] + v[ 7] * p[14];
	mvp[ 7] = v[ 4] * p[ 3] + v[ 5] * p[ 7] + v[ 6] * p[11] + v[ 7] * p[15];

	mvp[ 8] = v[ 8] * p[ 0] + v[ 9] * p[ 4] + v[10] * p[ 8] + v[11] * p[12];
	mvp[ 9] = v[ 8] * p[ 1] + v[ 9] * p[ 5] + v[10] * p[ 9] + v[11] * p[13];
	mvp[10] = v[ 8] * p[ 2] + v[ 9] * p[ 6] + v[10] * p[10] + v[11] * p[14];
	mvp[11] = v[ 8] * p[ 3] + v[ 9] * p[ 7] + v[10] * p[11] + v[11] * p[15];

	mvp[12] = v[12] * p[ 0] + v[13] * p[ 4] + v[14] * p[ 8] + v[15] * p[12];
	mvp[13] = v[12] * p[ 1] + v[13] * p[ 5] + v[14] * p[ 9] + v[15] * p[13];
	mvp[14] = v[12] * p[ 2] + v[13] * p[ 6] + v[14] * p[10] + v[15] * p[14];
	mvp[15] = v[12] * p[ 3] + v[13] * p[ 7] + v[14] * p[11] + v[15] * p[15];

	m_fPlanes[0][0] = mvp[ 3] - mvp[ 0];
	m_fPlanes[0][1] = mvp[ 7] - mvp[ 4];
	m_fPlanes[0][2] = mvp[11] - mvp[ 8];
	m_fPlanes[0][3] = mvp[15] - mvp[12];

	fDist = (float) sqrt (
		m_fPlanes[0][0] * m_fPlanes[0][0] +
		m_fPlanes[0][1] * m_fPlanes[0][1] +
		m_fPlanes[0][2] * m_fPlanes[0][2]
	);

	m_fPlanes[0][0] /= fDist;
	m_fPlanes[0][1] /= fDist;
	m_fPlanes[0][2] /= fDist;
	m_fPlanes[0][3] /= fDist;

	m_fPlanes[1][0] = mvp[ 3] + mvp[ 0];
	m_fPlanes[1][1] = mvp[ 7] + mvp[ 4];
	m_fPlanes[1][2] = mvp[11] + mvp[ 8];
	m_fPlanes[1][3] = mvp[15] + mvp[12];

	fDist = (float) sqrt (
		m_fPlanes[1][0] * m_fPlanes[1][0] +
		m_fPlanes[1][1] * m_fPlanes[1][1] +
		m_fPlanes[1][2] * m_fPlanes[1][2]
	);

	m_fPlanes[1][0] /= fDist;
	m_fPlanes[1][1] /= fDist;
	m_fPlanes[1][2] /= fDist;
	m_fPlanes[1][3] /= fDist;

	m_fPlanes[2][0] = mvp[ 3] + mvp[ 1];
	m_fPlanes[2][1] = mvp[ 7] + mvp[ 5];
	m_fPlanes[2][2] = mvp[11] + mvp[ 9];
	m_fPlanes[2][3] = mvp[15] + mvp[13];

	fDist = (float) sqrt (
		m_fPlanes[2][0] * m_fPlanes[2][0] +
		m_fPlanes[2][1] * m_fPlanes[2][1] +
		m_fPlanes[2][2] * m_fPlanes[2][2]
	);

	m_fPlanes[2][0] /= fDist;
	m_fPlanes[2][1] /= fDist;
	m_fPlanes[2][2] /= fDist;
	m_fPlanes[2][3] /= fDist;

	m_fPlanes[3][0] = mvp[ 3] - mvp[ 1];
	m_fPlanes[3][1] = mvp[ 7] - mvp[ 5];
	m_fPlanes[3][2] = mvp[11] - mvp[ 9];
	m_fPlanes[3][3] = mvp[15] - mvp[13];

	fDist = (float) sqrt (
		m_fPlanes[3][0] * m_fPlanes[3][0] +
		m_fPlanes[3][1] * m_fPlanes[3][1] +
		m_fPlanes[3][2] * m_fPlanes[3][2]
	);

	m_fPlanes[3][0] /= fDist;
	m_fPlanes[3][1] /= fDist;
	m_fPlanes[3][2] /= fDist;
	m_fPlanes[3][3] /= fDist;

	m_fPlanes[4][0] = mvp[ 3] - mvp[ 2];
	m_fPlanes[4][1] = mvp[ 7] - mvp[ 6];
	m_fPlanes[4][2] = mvp[11] - mvp[10];
	m_fPlanes[4][3] = mvp[15] - mvp[14];

	fDist = (float) sqrt (
		m_fPlanes[4][0] * m_fPlanes[4][0] +
		m_fPlanes[4][1] * m_fPlanes[4][1] +
		m_fPlanes[4][2] * m_fPlanes[4][2]
	);

	m_fPlanes[4][0] /= fDist;
	m_fPlanes[4][1] /= fDist;
	m_fPlanes[4][2] /= fDist;
	m_fPlanes[4][3] /= fDist;

	m_fPlanes[5][0] = mvp[ 3] + mvp[ 2];
	m_fPlanes[5][1] = mvp[ 7] + mvp[ 6];
	m_fPlanes[5][2] = mvp[11] + mvp[10];
	m_fPlanes[5][3] = mvp[15] + mvp[14];

	fDist = (float) sqrt (
		m_fPlanes[5][0] * m_fPlanes[5][0] +
		m_fPlanes[5][1] * m_fPlanes[5][1] +
		m_fPlanes[5][2] * m_fPlanes[5][2]
	);

	m_fPlanes[5][0] /= fDist;
	m_fPlanes[5][1] /= fDist;
	m_fPlanes[5][2] /= fDist;
	m_fPlanes[5][3] /= fDist;
}

}; // namespace gtl
