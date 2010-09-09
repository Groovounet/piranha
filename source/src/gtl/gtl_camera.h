//////////////////////////////////////////////////////////////////////////////
// GTL
// Copyright (c) 2003-2004 Groove
// Sous licence LGPL version 2
// G-Truc Creation, www.g-truc.net
//////////////////////////////////////////////////////////////////////////////
//! \date 01/06/2004
//! \file gtl_camera.h
//! \brief Classe CCamera, pour la visualisation d'une scène.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "gtl_vector2.h"
#include "gtl_vector3.h"

namespace gtl {

typedef enum
{
	CAMERA_NULL = (1<<0),
	CAMERA_FRUSTUM = (1<<1),
	CAMERA_TURN_OVER = (1<<2)
} ECameraOption;

//! \brief Classe pour la visualisation d'une scène.
class CCamera
{
private:
	CVector3<float> m_Position;
	CVector3<float> m_View;
	CVector3<float> m_UpVector;
	float m_fViewDistance;
	float m_fCurrentRotX;
	float m_fPlanes[6][4];
	unsigned int m_uiOption;

	void CalculatePlanes ();
	void RotateView (float angle, const CVector3<float> & Axis);
	void UpdateView (float iMoveZ, float fMoveX);

public:	
    CCamera ();
    ~CCamera ();

	void Enable (unsigned int uiOption);
	void Disable (unsigned int uiOption);
    void Init (const CVector3<float> & Position, const CVector3<float> & View);
	void LookAt ();
	void LookAt (const CVector3<float> & View);
	void LookAt (float fMoveZ, float fMoveX);
	void LookAt (const CVector3<float> & Position, const CVector3<float> & View);
	void Position (const CVector3<float> & Position, float fMoveZ, float fMoveX);
	void Move (float fSpeed);
	void Strafe (float fSpeed);
	void MoveUp (float fSpeed);
	CVector3<float> GetPosition () const {return m_Position;}
	CVector3<float> GetView () const {return m_View;}
	float GetDistance (float x, float y, float z = 0.f);
	float GetDistance (float *fCoord);
	bool TestDistance (float x, float y, float z = 0.f);
	bool IsInFrustum (float *fCoord, float fRadius = 1.f);
	bool IsInFrustum (float x, float y, float z, float fRadius = 1.f);
    float GetViewDistance () const {return m_fViewDistance;}
    void SetViewDistance (float fViewDistance) {m_fViewDistance = fViewDistance;}
};

}; //namespace gtl

#endif //__CAMERA_H__
