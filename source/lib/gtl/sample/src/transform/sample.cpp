/***********************************************\
	GTL sample : Transformation
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	sample.cpp, 03/10/2004
\***********************************************/

#include "./sample.h"
#include "./fps.h"

static float g_fRotationX = 0.0f;
static float g_fRotationY = 0.0f;
static float g_fRotationZ = 0.0f;
unsigned int g_uiTransformMode = 1;
CFPSCounter *g_pFPS = 0;
gtl::CFontTGA *g_pFont = 0;

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
	glEnd();
}

void TransformationMatrix ()
{
	gtl::CMatrix4x4<float> MatrixS;
	gtl::CMatrix4x4<float> MatrixTX;
	gtl::CMatrix4x4<float> MatrixTY;
	gtl::CMatrix4x4<float> MatrixRX;
	gtl::CMatrix4x4<float> MatrixRY;
	gtl::CMatrix4x4<float> MatrixRZ;

	MatrixRX.RotateX (g_fRotationX);
	MatrixRY.RotateY (g_fRotationY);
	MatrixRZ.RotateZ (g_fRotationZ);
	MatrixTX.Translate (3, 0, 0);
	MatrixTY.Translate (0,-3, 0);
	MatrixS.Scale (3, 2, 1);

	glMultMatrixf (MatrixS * MatrixRZ * MatrixRY * MatrixRX * MatrixTX * MatrixRZ * MatrixRY * MatrixRX * MatrixTY);
/*  ou : 
	glMultMatrixf (MatrixTY);
	glMultMatrixf (MatrixRX);
	glMultMatrixf (MatrixRY);
	glMultMatrixf (MatrixRZ);
	glMultMatrixf (MatrixTX);
	glMultMatrixf (MatrixRX);
	glMultMatrixf (MatrixRY);
	glMultMatrixf (MatrixRZ);
	glMultMatrixf (MatrixS);
*/
}

void TransformationQuaternion ()
{
	gtl::CMatrix4x4<float> MatrixS;
	gtl::CMatrix4x4<float> MatrixTX;
	gtl::CMatrix4x4<float> MatrixTY;
	gtl::CQuaternion<float> QuaternionX;
	gtl::CQuaternion<float> QuaternionY;
	gtl::CQuaternion<float> QuaternionZ;

	MatrixTX.Translate (3, 0, 0);
	MatrixTY.Translate (0,-3, 0);
	MatrixS.Scale (3, 2, 1);

	QuaternionX.RotateX (g_fRotationX);
	QuaternionY.RotateY (g_fRotationY);
	QuaternionZ.RotateZ (g_fRotationZ);

	glMultMatrixf (MatrixTY);
	glMultMatrixf (QuaternionX.GetMatrix ());
	glMultMatrixf (QuaternionY.GetMatrix ());
	glMultMatrixf (QuaternionZ.GetMatrix ());
	glMultMatrixf (MatrixTX);
	glMultMatrixf (QuaternionX.GetMatrix ());
	glMultMatrixf (QuaternionY.GetMatrix ());
	glMultMatrixf (QuaternionZ.GetMatrix ());
	glMultMatrixf (MatrixS);
}

void TransformationOpenGL ()
{
	glTranslatef (0,-3, 0);
	glRotatef (g_fRotationX, 1.0f, 0.0f, 0.0f);
	glRotatef (g_fRotationY, 0.0f, 1.0f, 0.0f);
	glRotatef (g_fRotationZ, 0.0f, 0.0f, 1.0f);
	glTranslatef (3, 0, 0);
	glRotatef (g_fRotationX, 1.0f, 0.0f, 0.0f);
	glRotatef (g_fRotationY, 0.0f, 1.0f, 0.0f);
	glRotatef (g_fRotationZ, 0.0f, 0.0f, 1.0f);
	glScalef (3, 2, 1);
}

bool Init ()
{
	g_pFPS = new CFPSCounter;
	g_pFPS->Init ();

	g_pFont = new gtl::CFontTGA;
	g_pFont->Load ("./data/font1.tga");

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);

	return true;
}

void Draw ()
{
	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity ();

	glPushMatrix ();
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		gluPerspective (45.f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 512);
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();

		gluLookAt (0, -16, 0,  0, 0, 0,  0, 0, 1);
	
		switch (g_uiTransformMode)
		{
		default:
		case 0:
			TransformationOpenGL ();
			break;
		case 1:
			TransformationMatrix ();
			break;
		case 2:
			TransformationQuaternion ();
			break;
		}
		
		glEnable (GL_CULL_FACE);
			Cube (0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		glDisable (GL_CULL_FACE);
	glPopMatrix ();

	glPushMatrix ();
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		glOrtho (0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		
		g_pFont->Begin ();
			g_pFont->Print (WINDOW_WIDTH - 16 * 8, WINDOW_HEIGHT - 16 * 1, "%d FPS", g_pFPS->GetFPS ());
			switch (g_uiTransformMode)
			{
			default:
			case 0:
				g_pFont->Print (0, 0, "OpenGL Transformation");
				break;
			case 1:
				g_pFont->Print (0, 0, "Matrix Transformation");
				break;
			case 2:
				g_pFont->Print (0, 0, "Quaternion Transformation");
				break;
			}
		g_pFont->End ();
	glPopMatrix ();

	g_fRotationX += 0.2f;
	g_fRotationY += 0.4f;
	g_fRotationZ += 0.8f;
	
	g_pFPS->Update ();
}

void End ()
{
	if (g_pFPS)
	{
		delete g_pFPS;
		g_pFPS = 0;
	}

	if (g_pFont)
	{
		delete g_pFont;
		g_pFont = 0;
	}
}
