/***********************************************\
	GTL sample
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	sample.cpp, 03/10/2004
\***********************************************/

#include "./sample.h"
#include "./terrain.h"

CTerrain *g_pTerrain = 0;
unsigned int g_uiTexture = 0;
bool g_bRot1 = false;
bool g_bRot2 = false;

bool Init ()
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel (GL_SMOOTH);

	g_pTerrain = new CTerrain;
	if (!g_pTerrain->Load ("./data/heightmap.tga", "./data/texture.tga"))
		return false;

	glLightfv (GL_LIGHT0, GL_AMBIENT, gtl::CColor4<float>(0.7f, 0.7f, 0.7f, 1.0));
	glLightfv (GL_LIGHT0, GL_DIFFUSE, gtl::CColor4<float>(0.9f, 0.9f, 0.9f, 1.0));
	glLightfv (GL_LIGHT0, GL_SPECULAR, gtl::CColor4<float>(1.0f, 1.0f, 1.0f, 1.0));
	glLightfv (GL_LIGHT0, GL_POSITION, gtl::CVector4<float>(1, 0, 0, 0));

	glLightfv (GL_LIGHT1, GL_AMBIENT, gtl::CColor4<float>(0.7f, 0.0f, 0.0f, 1.0));
	glLightfv (GL_LIGHT1, GL_DIFFUSE, gtl::CColor4<float>(0.9f, 0.0f, 0.0f, 1.0));
	glLightfv (GL_LIGHT1, GL_SPECULAR, gtl::CColor4<float>(1.0f, 0.0f, 0.0f, 1.0));
	glLightfv (GL_LIGHT1, GL_POSITION, gtl::CVector4<float>(1, 0, 0, 0));

	glLightfv (GL_LIGHT2, GL_AMBIENT, gtl::CColor4<float>(0.0f, 0.7f, 0.0f, 1.0));
	glLightfv (GL_LIGHT2, GL_DIFFUSE, gtl::CColor4<float>(0.0f, 0.9f, 0.0f, 1.0));
	glLightfv (GL_LIGHT2, GL_SPECULAR, gtl::CColor4<float>(0.0f, 1.0f, 0.0f, 1.0));
	glLightfv (GL_LIGHT2, GL_POSITION, gtl::CVector4<float>(1, 0, 0, 0));

	glLightfv (GL_LIGHT3, GL_AMBIENT, gtl::CColor4<float>(0.0f, 0.0f, 0.7f, 1.0));
	glLightfv (GL_LIGHT3, GL_DIFFUSE, gtl::CColor4<float>(0.0f, 0.0f, 0.9f, 1.0));
	glLightfv (GL_LIGHT3, GL_SPECULAR, gtl::CColor4<float>(0.0f, 0.0f, 1.0f, 1.0));
	glLightfv (GL_LIGHT3, GL_POSITION, gtl::CVector4<float>(1, 0, 0, 0));

	glEnable (GL_LIGHT0);
	glEnable (GL_LIGHT1);
	glEnable (GL_LIGHT2);
	glEnable (GL_LIGHT3);

	glEnable (GL_LIGHTING);
	glEnable (GL_DEPTH_TEST);

	return true;
}

void End ()
{
	delete g_pTerrain;
}

void Draw ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity ();
	gluLookAt (0, -256, 256, 0, 0, 0, 0, 0, 1);

	static float fRotSun = -90.f;
	static float fRotTerrain = 0;

	static float fRotR = 0.f;
	static float fRotG = 0.f;
	static float fRotB = 0.f;

	glPushMatrix ();
		glRotatef (fRotSun, 0.0f, 1.0f, 0.0f);
		glTranslated (0, 0, 256);
		glLightfv (GL_LIGHT0, GL_POSITION, gtl::CVector4<float>(1, 0, 0, 0));
	glPopMatrix ();

	glPushMatrix ();
		glRotatef (fRotR, 0.0f, 0.0f, 1.0f);
		glTranslated (256, 0, 0);
		glLightfv (GL_LIGHT1, GL_POSITION, gtl::CVector4<float>(1, 0, 0, 0));
	glPopMatrix ();
	glPushMatrix ();
		glRotatef (fRotG, 0.0f, 0.0f, 1.0f);
		glTranslated (256, 0, 0);
		glLightfv (GL_LIGHT2, GL_POSITION, gtl::CVector4<float>(1, 0, 0, 0));
	glPopMatrix ();
	glPushMatrix ();
		glRotatef (fRotB, 0.0f, 0.0f, 1.0f);
		glTranslated (256, 0, 0);
		glLightfv (GL_LIGHT3, GL_POSITION, gtl::CVector4<float>(1, 0, 0, 0));
	glPopMatrix ();

	glPushMatrix ();
		glRotatef (fRotTerrain, 0.0f, 0.0f, 1.0f);
		g_pTerrain->Draw ();
	glPopMatrix ();

	fRotR += 1.0f;
	if (fRotR > 360.f)
		fRotR = 0.f;

	fRotG += 2.0f;
	if (fRotG > 360.f)
		fRotG = 0.f;

	fRotB += 3.0f;
	if (fRotB > 360.f)
		fRotB = 0.f;

	fRotSun += 4.0f;
	if (fRotSun > 360.f)
		fRotSun = 0.f;

	if (g_bRot1)
		fRotTerrain++;
	if (g_bRot2)
		fRotTerrain--;
}

