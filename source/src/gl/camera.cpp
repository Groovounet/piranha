//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 01-06-2004
//! \file ./gl/camera.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./camera.h"

using namespace gl;

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

void CCamera::Init (const gtl::CVector3<float> & Position, const gtl::CVector3<float> & View)
{
    m_Position = Position;
    m_View = View;
}

void CCamera::LookAt (float fMoveZ, float fMoveX)
{
	UpdateView (fMoveZ / 10.f, fMoveX / 10.f);

	gluLookAt (
        m_Position (gtl::X), m_Position (gtl::Y), m_Position (gtl::Z),
		m_View (gtl::X), m_View (gtl::Y), m_View (gtl::Z),	
		m_UpVector (gtl::X), m_UpVector (gtl::Y), m_UpVector (gtl::Z)
	);

	if (m_uiOption & CAMERA_FRUSTUM)
		CalculatePlanes ();
}

void CCamera::LookAt (const gtl::CVector3<float> & View)
{
	m_View = m_Position + View;

	gluLookAt (
		m_Position (gtl::X), m_Position (gtl::Y), m_Position (gtl::Z),
		m_View (gtl::X), m_View (gtl::Y), m_View (gtl::Z),	
		m_UpVector (gtl::X), m_UpVector (gtl::Y), m_UpVector (gtl::Z)
	);

	if (m_uiOption & CAMERA_FRUSTUM)
		CalculatePlanes ();
}

void CCamera::LookAt (const gtl::CVector3<float> & Position, const gtl::CVector3<float> & View)
{
	gluLookAt (
		Position (gtl::X), Position (gtl::Y), Position (gtl::Z),	
		View (gtl::X), View (gtl::Y), View (gtl::Z),	
		m_UpVector (gtl::X), m_UpVector (gtl::Y), m_UpVector (gtl::Z)
	);

	if (m_uiOption & CAMERA_FRUSTUM)
		CalculatePlanes ();
}

void CCamera::LookAt ()
{
	gluLookAt (
		m_Position (gtl::X), m_Position (gtl::Y), m_Position (gtl::Z),
		m_View (gtl::X), m_View (gtl::Y), m_View (gtl::Z),
		m_UpVector (gtl::X), m_UpVector (gtl::Y), m_UpVector (gtl::Z)
	);
}

void CCamera::Position (const gtl::CVector3<float> & Position, float fMoveZ, float fMoveX)
{
	Move (Position (gtl::X));
	Strafe (Position (gtl::Y));
	MoveUp (Position (gtl::Z));

	UpdateView (fMoveZ, fMoveX);
}

void CCamera::UpdateView (float fMoveZ, float fMoveX)
{
	if ((fMoveX == 0) && (fMoveZ == 0))
		return;

	float fAngleX = gtl::CMath<float>::DegToRad(fMoveX);
	float fAngleZ = gtl::CMath<float>::DegToRad(fMoveZ);
	
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

	gtl::CVector3<float> Axis = ((m_View - m_Position) ^ m_UpVector).GetNormalize ();

	RotateView (fAngleX, Axis);
	RotateView (fAngleZ, m_UpVector);
}

void CCamera::RotateView (float fAngle, const gtl::CVector3<float> & Axis)
{
	gtl::CVector3<float> NewView;
	gtl::CVector3<float> View = m_View - m_Position;		

	float fCosTheta = cosf (fAngle);
	float fSinTheta = sinf (fAngle);

	NewView (gtl::X)  = (fCosTheta + (1 - fCosTheta) * Axis(gtl::X) * Axis(gtl::X)) * View (gtl::X);
	NewView (gtl::X) += ((1 - fCosTheta) * Axis(gtl::X) * Axis(gtl::Y) - Axis(gtl::Z) * fSinTheta) * View (gtl::Y);
	NewView (gtl::X) += ((1 - fCosTheta) * Axis(gtl::X) * Axis(gtl::Z) + Axis(gtl::Y) * fSinTheta) * View (gtl::Z);

	NewView (gtl::Y)  = ((1 - fCosTheta) * Axis(gtl::X) * Axis(gtl::Y) + Axis(gtl::Z) * fSinTheta) * View (gtl::X);
	NewView (gtl::Y) += (fCosTheta + (1 - fCosTheta) * Axis(gtl::Y) * Axis(gtl::Y)) * View (gtl::Y);
	NewView (gtl::Y) += ((1 - fCosTheta) * Axis(gtl::Y) * Axis(gtl::Z) - Axis(gtl::X) * fSinTheta) * View (gtl::Z);

	NewView (gtl::Z)  = ((1 - fCosTheta) * Axis(gtl::X) * Axis(gtl::Z) - Axis(gtl::Y) * fSinTheta) * View (gtl::X);
	NewView (gtl::Z) += ((1 - fCosTheta) * Axis(gtl::Y) * Axis(gtl::Z) + Axis(gtl::X) * fSinTheta) * View (gtl::Y);
	NewView (gtl::Z) += (fCosTheta + (1 - fCosTheta) * Axis(gtl::Z) * Axis(gtl::Z)) * View (gtl::Z);

	m_View = m_Position + NewView;
}

void CCamera::Move (float fSpeed)
{
	gtl::CVector3<float> Vector = m_View - m_Position;

	m_Position += Vector * fSpeed;
	m_View += Vector * fSpeed;
}

void CCamera::Strafe (float fSpeed)
{
	gtl::CVector3<float> Vector = (m_View - m_Position) ^ m_UpVector;

	m_Position += Vector * fSpeed;
	m_View += Vector * fSpeed;
}

void CCamera::MoveUp (float fSpeed)
{
	gtl::CVector3<float> Vector = m_UpVector;

	m_Position += Vector * fSpeed;
	m_View += Vector * fSpeed;
}

float CCamera::GetDistance (float x, float y, float z)
{
	return gtl::CMath<float>::Sqr (m_Position (gtl::X) - x) + gtl::CMath<float>::Sqr (m_Position (gtl::Y) - y) + gtl::CMath<float>::Sqr (m_Position (gtl::Z) - z);
}

float CCamera::GetDistance (float *fCoord)
{
	return gtl::CMath<float>::Sqr (m_Position (gtl::X) - fCoord[0]) + gtl::CMath<float>::Sqr (m_Position (gtl::Y) - fCoord[1]) + gtl::CMath<float>::Sqr (m_Position (gtl::Z) - fCoord[2]);
}

bool CCamera::TestDistance (float x, float y, float z)
{
	if ((gtl::CMath<float>::Sqr (m_Position (gtl::X) - x) + gtl::CMath<float>::Sqr (m_Position (gtl::Y) - y) + gtl::CMath<float>::Sqr (m_Position (gtl::Z) - z)) > gtl::CMath<float>::Sqr (m_fViewDistance))
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
