//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./gl/object_ge.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_GL_OBJECT_GE_H__
#define __PIRANHA_GL_OBJECT_GE_H__

#include "./object.h"

namespace gl {

class CObjectGE : public CObject
{
private:

public:
    CObjectGE ();
    virtual ~CObjectGE ();

    void Cube (const gtl::CVector3<float> & Position, const gtl::CVector3<float> & Size);
    void Cylinder (float fRadius, float fLenght, float fDivisionX, float fDivisionZ);
    //void Elipse (const gtl::CVector3<float> & Position, unsigned int uiHorizontal, unsigned int uiVertical);
    void Plane (const gtl::CVector3<float> & Position, const gtl::CVector2<float> & Size, const gtl::CVector2<float> & Division);
    void Sphere (float fRayon, unsigned int uiHorizontal, unsigned int uiVertical);
};

}; // gl

#endif //__PIRANHA_GL_OBJECT_GE_H__
