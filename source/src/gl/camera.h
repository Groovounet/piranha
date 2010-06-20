//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 01-06-2004
//! \file ./piranha/gl/camera.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_GL_CAMERA_H__
#define __PIRANHA_GL_CAMERA_H__

#include "../util/common.h"
#include "../util/singleton.h"

namespace gl {

typedef enum
{
	CAMERA_NULL = (1<<0),
	CAMERA_FRUSTUM = (1<<1),
	CAMERA_TURN_OVER = (1<<2)
} ECameraOption;

class CCamera : public util::CSingleton<CCamera>
{
    friend class util::CSingleton<CCamera>;

private:
    gtl::CVector3<float> m_Position;
	gtl::CVector3<float> m_View;
	gtl::CVector3<float> m_UpVector;
	float m_fViewDistance;
	float m_fCurrentRotX;
	float m_fPlanes[6][4];
	unsigned int m_uiOption;

	void CalculatePlanes ();
	void RotateView (float angle, const gtl::CVector3<float> & Axis);
	void UpdateView (float iMoveZ, float fMoveX);

public:	
    CCamera ();
    ~CCamera ();

	void Enable (unsigned int uiOption);
	void Disable (unsigned int uiOption);
    void Init (const gtl::CVector3<float> & Position, const gtl::CVector3<float> & View);
	void LookAt ();
	void LookAt (const gtl::CVector3<float> & View);
	void LookAt (float fMoveZ, float fMoveX);
	void LookAt (const gtl::CVector3<float> & Position, const gtl::CVector3<float> & View);
	void Position (const gtl::CVector3<float> & Position, float fMoveZ, float fMoveX);
	void Move (float fSpeed);
	void Strafe (float fSpeed);
	void MoveUp (float fSpeed);
    gtl::CVector3<float> GetPosition () const {return m_Position;}
	gtl::CVector3<float> GetView () const {return m_View;}
	float GetDistance (float x, float y, float z = 0.f);
	float GetDistance (float *fCoord);
	bool TestDistance (float x, float y, float z = 0.f);
	bool IsInFrustum (float *fCoord, float fRadius = 1.f);
	bool IsInFrustum (float x, float y, float z, float fRadius = 1.f);
    float GetViewDistance () const {return m_fViewDistance;}
    void SetViewDistance (float fViewDistance) {m_fViewDistance = fViewDistance;}
};

}; // gl

#endif //__PIRANHA_GL_CAMERA_H__
