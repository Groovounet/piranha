/***********************************************\
	GTL sample : font
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	font.cpp, 03/10/2004
\***********************************************/

#include "./sample.h"

gtl::CFontTGA g_Font;
gtl::CScreenshot g_Screenshot;

float theta = 0.0f;
unsigned int g_uiTextureIndex;
bool g_bScreenshot = false;

bool Init ()
{
	glClearDepth (1.0f);
	glDepthFunc (GL_LEQUAL);

	g_Font.Load ("./data/font1.tga");
	g_Font.Enable (gtl::FONT_BLEND | gtl::FONT_SCALE | gtl::FONT_SPACING);
	g_Font.Color (1.0f, 1.0f, 1.0f);
	g_Font.Size (16.f, 32.f);
	g_Font.Spacing (10);

	g_Screenshot.Config (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	return true;
}

void Draw ()
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity ();

	glPushMatrix ();
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		glOrtho (-1, 1, -1, 1, -1, 1);
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();

		glRotatef (theta, 0.0f, 0.0f, 1.0f);
		glBegin (GL_TRIANGLES);
			glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (0.0f, 1.0f);
			glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (0.87f, -0.5f);
			glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (-0.87f, -0.5f);
		glEnd ();
	glPopMatrix ();

	theta += 1.0f;

	glPushMatrix ();
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		glOrtho (0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		
		g_Font.Begin ();
			g_Font.Print (0, 0, "Coucou : %d", 76);
   			g_Font.Print (0, 32, "G-Truc Creation");
   			g_Font.Print (0, 64, "abcdefghijklmnopqrstuvwxyz");
   			g_Font.Print (0, 96, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   			g_Font.Print (0, 128, "0123456789");
		g_Font.End ();
	glPopMatrix ();

	if (!g_bScreenshot)
	{
		g_bScreenshot = true;
		g_Screenshot.Snap ("snap");
	}
}
