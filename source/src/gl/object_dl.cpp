//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-17-2004
//! \file ./gl/object_dl.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./object_dl.h"
#include "./proc.h"

using namespace gl;

CObjectDL::CObjectDL ()
{
    m_uiDisplayList = glGenLists (1);
}

CObjectDL::~CObjectDL ()
{
    glDeleteLists (m_uiDisplayList, 1);
}

void CObjectDL::Render () const
{
    glCallList (m_uiDisplayList);
}

void CObjectDL::Cube (const gtl::CVector3<float> & Position, const gtl::CVector3<float> & Size)
{
    glNewList(m_uiDisplayList, GL_COMPILE);

    float x = Position (gtl::X) - Size (gtl::X)  / 2;
	float y = Position (gtl::Y) - Size (gtl::Y) / 2;
	float z = Position (gtl::Z) - Size (gtl::Z) / 2;

	glBegin (GL_QUADS);		
		// Upper side
        {
            if (m_bColor)
		        glColor3f (1.0, 0.0, 0.0);

            if (m_Normal != NORMAL_NONE)
                glNormal3f (0, 0, 1);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 1);
		    glVertex3f (x, y, z);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 0);
		    glVertex3f (x, y + Size (gtl::Y), z);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 0);
		    glVertex3f (x + Size (gtl::X), y + Size (gtl::Y), z); 

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 1);
		    glVertex3f (x + Size (gtl::X), y, z);
        }

		// Lower side
        {
            if (m_bColor)
		        glColor3f (0.0, 1.0, 1.0);

            if (m_Normal != NORMAL_NONE)
                glNormal3f (0, 0, -1);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 0);
		    glVertex3f (x, y, z + Size (gtl::Z));

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 0);
		    glVertex3f (x + Size (gtl::X), y, z + Size (gtl::Z));

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 1);
		    glVertex3f (x + Size (gtl::X), y + Size (gtl::Y), z + Size (gtl::Z)); 

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 1);
		    glVertex3f (x, y + Size (gtl::Y), z + Size (gtl::Z));
        }

		// forward side 
        {
            if (m_bColor)
		        glColor3f (0.0, 1.0, 0.0);

            if (m_Normal != NORMAL_NONE)
                glNormal3f (0, -1, 0);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 0);
		    glVertex3f (x, y, z);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 0);
            glVertex3f (x + Size (gtl::X), y, z);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 1);
            glVertex3f (x + Size (gtl::X), y, z + Size (gtl::Z)); 

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 1);
		    glVertex3f (x, y, z + Size (gtl::Z));
        }

		// backward side
        {
            if (m_bColor)
		        glColor3f (1.0, 0.0, 1.0);

            if (m_Normal != NORMAL_NONE)
                glNormal3f (0, 1, 0);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 0);
		    glVertex3f (x, y + Size (gtl::Y), z);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 1);
		    glVertex3f (x, y + Size (gtl::Y), z + Size (gtl::Z));

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 1);
		    glVertex3f (x + Size (gtl::X), y + Size (gtl::Y), z + Size (gtl::Z)); 

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 0);
		    glVertex3f (x + Size (gtl::X), y + Size (gtl::Y), z);
        }

		// left side
        {
            if (m_bColor)
		        glColor3f (0.0, 0.0, 1.0);

            if (m_Normal != NORMAL_NONE)
                glNormal3f (-1, 0, 0);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 0);
		    glVertex3f (x, y, z);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 1);
		    glVertex3f (x, y, z + Size (gtl::Z));

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 1);
		    glVertex3f (x, y + Size (gtl::Y), z + Size (gtl::Z)); 

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 0);
		    glVertex3f (x, y + Size (gtl::Y), z);
        }

		// right side
        {
            if (m_bColor)
		        glColor3f (1.0, 1.0, 0.0);

            if (m_Normal != NORMAL_NONE)
                glNormal3f (1, 0, 0);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 0);
            glVertex3f (x + Size (gtl::X), y, z);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 0);
            glVertex3f (x + Size (gtl::X), y + Size (gtl::Y), z);

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 1, 1);
            glVertex3f (x + Size (gtl::X), y + Size (gtl::Y), z + Size (gtl::Z)); 

            for (int k = 0; k < 8; k++)
                if (m_uiTexture & (1 << k))
                    glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, 0, 1);
            glVertex3f (x + Size (gtl::X), y, z + Size (gtl::Z));
        }
	glEnd ();

    glEndList ();
}

void CObjectDL::Cylinder (float fRadius, float fLenght, float fDivisionX, float fDivisionZ)
{
    glNewList (m_uiDisplayList, GL_COMPILE);

    float fIncX = 2.f * (float)PI / fDivisionX;
    float fIncZ = fLenght / fDivisionZ;

    for (float i = 0; i < fDivisionZ; i += fIncZ)
    {
        glBegin (GL_QUADS);
        //glBegin (GL_LINE_STRIP);
            for (float j = 0.0f; j < 2.f * (float)PI; j += fIncX)
            {    
                float x1 = fRadius * sinf (j);
                float y1 = fRadius * cosf (j);
                float x2 = fRadius * sinf (j + fIncX);
                float y2 = fRadius * cosf (j + fIncX);

                for (int k = 0; k < TEXTURE_MAX; k++)
                    if (m_uiTexture & (1 << k))
                        glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, (float) j / fDivisionX, (float) (i + 0) / fDivisionZ);
                glNormal3f (x1, y1, 0);
                glVertex3f (x1, y1, (i + 0) * fIncZ);

                for (int k = 0; k < TEXTURE_MAX; k++)
                    if (m_uiTexture & (1 << k))
                        glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, (float) j / fDivisionX, (float) (i + 1) / fDivisionZ);
                glNormal3f (x1, y1, 0);
                glVertex3f (x1, y1, (i + 1) * fIncZ);

                for (int k = 0; k < TEXTURE_MAX; k++)
                    if (m_uiTexture & (1 << k))
                        glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, (float) j / fDivisionX, (float) (i + 1) / fDivisionZ);
                glNormal3f (x2, y2, 0);
                glVertex3f (x2, y2, (i + 1) * fIncZ);

                for (int k = 0; k < TEXTURE_MAX; k++)
                    if (m_uiTexture & (1 << k))
                        glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, (float) j / fDivisionX, (float) (i + 0) / fDivisionZ);
                glNormal3f (x2, y2, 0);
                glVertex3f (x2, y2, (i + 0) * fIncZ);
            }
        glEnd ();
    }

    glEndList ();
}

void CObjectDL::Plane (const gtl::CVector3<float> & Position, const gtl::CVector2<float> & Size, const gtl::CVector2<float> & Division)
{
    glNewList (m_uiDisplayList, GL_COMPILE);

    float x = Position (gtl::X) - Size (gtl::X) / 2;
	float y = Position (gtl::Y) - Size (gtl::Y) / 2;
    float z = Position (gtl::Z);

	glBegin (GL_QUADS);		
        if (m_bColor)
		    glColor4fv (m_Color);

        if (m_Normal != NORMAL_NONE)
            glNormal3f (0, 0, 1);

        float fVtxIncX = Size (gtl::X) / Division (gtl::X);
        float fVtxIncY = Size (gtl::Y) / Division (gtl::Y);
        float fTexIncX = 1.0f / Division (gtl::X);
        float fTexIncY = 1.0f / Division (gtl::Y);
        for (int j = 0; j < Division (gtl::Y); j++)
        {
            for (int i = 0; i < Division (gtl::X); i++)
            {
                for (int k = 0; k < 8; k++)
                    if (m_uiTexture & (1 << k))
                        glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, (i + 0) * fTexIncX, (j + 0) * fTexIncY);
		        glVertex3f (x + (i + 0) * fVtxIncX, y + (j + 0) * fVtxIncY, z);

                for (int k = 0; k < 8; k++)
                    if (m_uiTexture & (1 << k))
                        glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, (i + 1) * fTexIncX, (j + 0) * fTexIncY);
                glVertex3f (x + (i + 1) * fVtxIncX, y + (j + 0) * fVtxIncY, z);

                for (int k = 0; k < 8; k++)
                    if (m_uiTexture & (1 << k))
                        glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, (i + 1) * fTexIncX, (j + 1) * fTexIncY);
                glVertex3f (x + (i + 1) * fVtxIncX, y + (j + 1) * fVtxIncY, z);

                for (int k = 0; k < 8; k++)
                    if (m_uiTexture & (1 << k))
                        glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, (i + 0) * fTexIncX, (j + 1) * fTexIncY);
                glVertex3f (x + (i + 0) * fVtxIncX, y + (j + 1) * fVtxIncY, z);
            }
        }
    glEnd ();

    glEndList ();
}

void CObjectDL::Sphere (float fRayon, unsigned int uiHorizontal, unsigned int uiVertical)
{
    glNewList (m_uiDisplayList, GL_COMPILE);

    float fHorizontal = (float)PI / uiHorizontal;
    float fVertical = 2.0f * ((float)PI / uiVertical);

    // Parcours horizontal
    for (unsigned int i = 0; i < uiHorizontal; i++)
    {
	    // Cercle horizontal courant
        float fPointCourantH = static_cast<float> (i) * fHorizontal;
        // Cercle horizontal suivant
	    float fPointSuivantH = fPointCourantH + fHorizontal;
	    
        // Positions en X
        float fPointCourantX = sinf (fPointCourantH) * fRayon;
	    float fPointSuivantX = sinf (fPointSuivantH) * fRayon;
	    
        // Positions en Z
        float fPointCourantZ = cosf (fPointCourantH) * fRayon;
	    float fPointSuivantZ = cosf (fPointSuivantH) * fRayon;
	
        glBegin (GL_TRIANGLE_STRIP);
            //glColor4fv (m_Color);
 	        // Parcours vertical
            for (unsigned int j = 0; j <= uiVertical; j++)
            {
                float fPointCourantV = static_cast<float> (j) * fVertical;            
                float x = cosf (fPointCourantV);
                float y = sinf (fPointCourantV);

                for (int k = 0; k < 8; k++)
                    if (m_uiTexture & (1 << k))
                        glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, (float) j / (float) uiVertical, (float) (i + 0) / (float) uiHorizontal);
                if (m_Normal & NORMAL_SMOOTH || m_Normal & NORMAL_FLAT)
                    glNormal3f (x * fPointCourantX, y * fPointCourantX, fPointCourantZ);
                glVertex3f (x * fPointCourantX, y * fPointCourantX, fPointCourantZ);
                for (int k = 0; k < 8; k++)
                    if (m_uiTexture & (1 << k))
                        glMultiTexCoord2fARB (GL_TEXTURE0_ARB + k, (float) j / (float) uiVertical, (float)(i + 1) / (float) uiHorizontal);
                if (m_Normal & NORMAL_SMOOTH || m_Normal & NORMAL_FLAT)
                    glNormal3f (x * fPointSuivantX, y * fPointSuivantX, fPointSuivantZ);
                glVertex3f (x * fPointSuivantX, y * fPointSuivantX, fPointSuivantZ);
            }	        
        glEnd ();
    }

    glEndList ();
}

void CObjectDL::Disk (float fRadius, unsigned int uiDivision)
{
    if (!uiDivision)
        return;

    float fAngle = 360.f / uiDivision;
    glNewList (m_uiDisplayList, GL_COMPILE);
        glBegin (GL_TRIANGLE_STRIP);
            glVertex3f (0, 0, 0);
            for (float i = 0; i <= 360; i += fAngle)
            {
                glVertex3f (cosf (i) * fRadius, sinf (i) * fRadius, 0);
            }
        glEnd ();
    glEndList ();
}
