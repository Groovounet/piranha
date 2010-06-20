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

typedef gtl::CVector4<float> TVector4;

typedef struct
{
	gtl::CPolynomial m_Polynomial;
	TVector4 m_Color;
} SCourbe;

SCourbe g_Courbe[12];

bool SetColor (unsigned char ucColor, double * pTime, TVector4 * pAmbient, TVector4 * pDiffuse, TVector4 * pSpecular)
{
	double* pfAmbientRed = new double [ucColor];
	double* pfAmbientGreen = new double [ucColor];
	double* pfAmbientBlue = new double [ucColor];
	double* pfAmbientAlpha = new double [ucColor];

	double* pfDiffuseRed = new double [ucColor];
	double* pfDiffuseGreen = new double [ucColor];
	double* pfDiffuseBlue = new double [ucColor];
	double* pfDiffuseAlpha = new double [ucColor];

	double* pfSpecularRed = new double [ucColor];
	double* pfSpecularGreen = new double [ucColor];
	double* pfSpecularBlue = new double [ucColor];
	double* pfSpecularAlpha = new double [ucColor];

	for (int i = 0; i < ucColor; i++)
	{
		pfAmbientRed [i] = pAmbient[i] (gtl::X);
		pfAmbientGreen [i] = pAmbient[i] (gtl::Y);
		pfAmbientBlue [i] = pAmbient[i] (gtl::Z);
		pfAmbientAlpha [i] = pAmbient[i] (gtl::W);

		pfDiffuseRed [i] = pDiffuse[i] (gtl::X);
		pfDiffuseGreen [i] = pDiffuse[i] (gtl::Y);
		pfDiffuseBlue [i] = pDiffuse[i] (gtl::Z);
		pfDiffuseAlpha [i] = pDiffuse[i] (gtl::W);

		pfSpecularRed [i] = pSpecular[i] (gtl::X);
		pfSpecularGreen [i] = pSpecular[i] (gtl::Y);
		pfSpecularBlue [i] = pSpecular[i] (gtl::Z);
		pfSpecularAlpha [i] = pSpecular[i] (gtl::W);
	}

	g_Courbe[ 0].m_Polynomial.Load (ucColor, pTime, pfAmbientRed);		g_Courbe[ 0].m_Color = TVector4 (0.5f, 0.0f, 0.0f, 1.0f);
	g_Courbe[ 1].m_Polynomial.Load (ucColor, pTime, pfAmbientGreen);	g_Courbe[ 1].m_Color = TVector4 (0.0f, 0.5f, 0.0f, 1.0f);
	g_Courbe[ 2].m_Polynomial.Load (ucColor, pTime, pfAmbientBlue);		g_Courbe[ 2].m_Color = TVector4 (0.0f, 0.0f, 0.5f, 1.0f);
	g_Courbe[ 3].m_Polynomial.Load (ucColor, pTime, pfAmbientAlpha);	g_Courbe[ 3].m_Color = TVector4 (0.5f, 0.5f, 0.5f, 1.0f);

	g_Courbe[ 4].m_Polynomial.Load (ucColor, pTime, pfDiffuseRed);		g_Courbe[ 4].m_Color = TVector4 (1.0f, 0.0f, 0.0f, 1.0f);
	g_Courbe[ 5].m_Polynomial.Load (ucColor, pTime, pfDiffuseGreen);	g_Courbe[ 5].m_Color = TVector4 (0.0f, 1.0f, 0.0f, 1.0f);
	g_Courbe[ 6].m_Polynomial.Load (ucColor, pTime, pfDiffuseBlue);		g_Courbe[ 6].m_Color = TVector4 (0.0f, 0.0f, 1.0f, 1.0f);
	g_Courbe[ 7].m_Polynomial.Load (ucColor, pTime, pfAmbientAlpha);	g_Courbe[ 7].m_Color = TVector4 (0.7f, 0.7f, 0.7f, 1.0f);

	g_Courbe[ 8].m_Polynomial.Load (ucColor, pTime, pfSpecularRed);		g_Courbe[ 8].m_Color = TVector4 (1.0f, 0.5f, 0.5f, 1.0f);
	g_Courbe[ 9].m_Polynomial.Load (ucColor, pTime, pfSpecularGreen);	g_Courbe[ 9].m_Color = TVector4 (0.5f, 1.0f, 0.5f, 1.0f);
	g_Courbe[10].m_Polynomial.Load (ucColor, pTime, pfSpecularBlue);	g_Courbe[10].m_Color = TVector4 (0.5f, 0.5f, 1.0f, 1.0f);
	g_Courbe[11].m_Polynomial.Load (ucColor, pTime, pfAmbientAlpha);	g_Courbe[11].m_Color = TVector4 (1.0f, 1.0f, 1.0f, 1.0f);

	delete [] pfAmbientRed;
	delete [] pfAmbientGreen;
	delete [] pfAmbientBlue;
	delete [] pfAmbientAlpha;

	delete [] pfDiffuseRed;
	delete [] pfDiffuseGreen;
	delete [] pfDiffuseBlue;
	delete [] pfDiffuseAlpha;

	delete [] pfSpecularRed;
	delete [] pfSpecularGreen;
	delete [] pfSpecularBlue;
	delete [] pfSpecularAlpha;

	return true;
}

bool Init ()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);

	TVector4 Ambience[] = 
	{
		TVector4 (1.0f, 1.0f, 0.7f, 0.2f),
		TVector4 (1.0f, 1.0f, 0.7f, 0.2f),
		TVector4 (1.0f, 0.8f, 0.5f, 0.4f),
		TVector4 (1.0f, 1.0f, 0.7f, 0.6f),
		TVector4 (1.0f, 0.8f, 0.5f, 0.4f),
		TVector4 (1.0f, 1.0f, 0.7f, 0.2f),
		TVector4 (1.0f, 1.0f, 0.7f, 0.2f),
	};
	TVector4 Diffuse[] = 
	{
		TVector4 (1.0f, 1.0f, 0.8f, 0.3f),
		TVector4 (1.0f, 1.0f, 0.8f, 0.3f),
		TVector4 (1.0f, 0.7f, 0.3f, 0.6f),
		TVector4 (1.0f, 1.0f, 0.8f, 0.9f),
		TVector4 (1.0f, 0.7f, 0.3f, 0.6f),
		TVector4 (1.0f, 1.0f, 0.8f, 0.3f),
		TVector4 (1.0f, 1.0f, 0.8f, 0.3f),
	};
	TVector4 Specular[] = 
	{
		TVector4 (1.0f, 1.0f, 0.9f, 0.5f),
		TVector4 (1.0f, 1.0f, 0.9f, 0.5f),
		TVector4 (1.0f, 0.5f, 0.0f, 0.7f),
		TVector4 (1.0f, 1.0f, 0.9f, 1.0f),
		TVector4 (1.0f, 0.5f, 0.0f, 0.7f),
		TVector4 (1.0f, 1.0f, 0.9f, 0.5f),
		TVector4 (1.0f, 1.0f, 0.9f, 0.5f),
	};
	double fTime[] = {0, 4, 6, 12, 18, 20, 24};

	SetColor (7, fTime, Ambience, Diffuse, Specular);

	return true;
}

void Draw ()
{
	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity ();

	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();
		glLoadIdentity ();
		glOrtho (0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();

		glPushMatrix ();
			glTranslated (-12, 0, 0);
			glBegin (GL_POINTS);
				glVertex2f (0, 0);
				glVertex2f (24, 0);
				glVertex2f (0, 4);
				glVertex2f (24, 4);
			glEnd ();
		glPopMatrix ();

		for (int j = 0; j < 12; j++)
		{
		glPushMatrix ();
			glTranslated (0, WINDOW_HEIGHT / 2, 0);
			glBegin (GL_LINE_STRIP);
				glColor4fv (g_Courbe[j].m_Color);
				for (float i = 0; i <= 24; i += 0.2f)
					glVertex3f (i*WINDOW_WIDTH/24, (float)g_Courbe[j].m_Polynomial (i) * 64, 0);
			glEnd ();
		glPopMatrix ();
		}

		glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
	glMatrixMode (GL_MODELVIEW);
}

void End ()
{

}

