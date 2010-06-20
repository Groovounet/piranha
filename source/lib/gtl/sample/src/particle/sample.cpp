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

CTerrain *g_pTerrain = 0;
CParticleSystem *g_pSystem = 0;
unsigned int g_uiTexture = 0;
bool g_bRotX1 = false;
bool g_bRotX2 = false;
bool g_bRotZ1 = false;
bool g_bRotZ2 = false;

void Cube (float x, float y, float z, float fLargeur, float fHauteur, float fLongueur)
{
	x = x - fLargeur  / 2;
	y = y - fHauteur / 2;
	z = z - fLongueur / 2;

	glBegin (GL_QUADS);		
		// face de dessous 
		glColor3f (1.0, 0.0, 0.0);
		glVertex3f (x, y, z);
		glVertex3f (x, y + fHauteur, z);
		glVertex3f (x + fLargeur, y + fHauteur, z); 
		glVertex3f (x + fLargeur, y, z);
	
		// face de dessus 
		glColor3f (0.0, 1.0, 1.0);
		glVertex3f (x, y, z + fLongueur);
		glVertex3f (x + fLargeur, y, z + fLongueur);
		glVertex3f (x + fLargeur, y + fHauteur, z + fLongueur); 
		glVertex3f (x, y + fHauteur, z + fLongueur);
	
		// face de devant 
		glColor3f (0.0, 1.0, 0.0);
		glVertex3f (x, y, z);
		glVertex3f (x + fLargeur, y, z);
		glVertex3f (x + fLargeur, y, z + fLongueur); 
		glVertex3f (x, y, z + fLongueur);

		// face de derrière
		glColor3f (1.0, 0.0, 1.0);
		glVertex3f (x, y + fHauteur, z);
		glVertex3f (x, y + fHauteur, z + fLongueur);
		glVertex3f (x + fLargeur, y + fHauteur, z + fLongueur); 
		glVertex3f (x + fLargeur, y + fHauteur, z);
	
		// face de gauche
		glColor3f (0.0, 0.0, 1.0);
		glVertex3f (x, y, z);
		glVertex3f (x, y, z + fLongueur);
		glVertex3f (x, y + fHauteur, z + fLongueur); 
		glVertex3f (x, y + fHauteur, z);

		// face de droite
		glColor3f (1.0, 1.0, 0.0);
		glVertex3f (x + fLargeur, y, z);
		glVertex3f (x + fLargeur, y + fHauteur, z);
		glVertex3f (x + fLargeur, y + fHauteur, z + fLongueur); 
		glVertex3f (x + fLargeur, y, z + fLongueur);
	glEnd ();
}

bool Init ()
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel (GL_SMOOTH);

	g_pTerrain = new CTerrain;
	if (!g_pTerrain->Load ("./data/heightmap.tga", "./data/texture.tga"))
		return false;

	g_pSystem = new CParticleSystem;
	if (!g_pSystem->Load ("./data/particle.tga"))
		return false;

	float Ambience[4] = {0.5f, 0.5f, 0.4f, 1.0};
	float Diffuse[4] = {0.7f, 0.7f, 0.6f, 1.0};
	float Specular[4] = {1.0f, 1.0f, 0.9f, 1.0};
	float LightPosition[4] = {0, 0, 2, 0};

	glLightfv (GL_LIGHT0, GL_AMBIENT, Ambience);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, Diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, Specular);
	glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);

	glEnable (GL_LIGHT0);
	glEnable (GL_LIGHTING);
	glEnable (GL_DEPTH_TEST);

	return true;
}

void End ()
{
	delete g_pTerrain;
	delete g_pSystem;
}

void Draw ()
{
	g_pSystem->Update ();

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity ();
	gluLookAt (0, -256, 256, 0, 0, 0, 0, 0, 1);
/*
	gtl::CMatrix4x4<float> Matrix;
	gtl::CVector3<float> Normal (1.0f, 1.0f, 1.0f);
	Normal.Normalize ();
	Matrix.Rotate (45, Normal);
	glMultMatrixf (Matrix);
*/
	static float fRotTerrainX = 0;
	static float fRotTerrainZ = 0;

	glPushMatrix ();
		glLightfv (GL_LIGHT0, GL_POSITION, gtl::CVector4<float>(0, -128, 128, 1));
	glPopMatrix ();

	glPushMatrix ();
		glRotatef (fRotTerrainX, 1.0f, 0.0f, 0.0f);
		glRotatef (fRotTerrainZ, 0.0f, 0.0f, 1.0f);
		glTranslated (-128, -128, 0);
		glEnable (GL_LIGHTING);
			g_pTerrain->Draw ();
		glDisable (GL_LIGHTING);
		Cube (128, 128, 128, 16, 16, 16);
		g_pSystem->Draw ();
	glPopMatrix ();

	if (g_bRotX1)
		fRotTerrainX++;
	if (g_bRotX2)
		fRotTerrainX--;
	if (g_bRotZ1)
		fRotTerrainZ++;
	if (g_bRotZ2)
		fRotTerrainZ--;
}

