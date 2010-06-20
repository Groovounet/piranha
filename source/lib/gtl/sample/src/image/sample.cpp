/***********************************************\
	GTL sample : image
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	sample.cpp, 03/10/2004
\***********************************************/

#include "./sample.h"

unsigned int g_uiTextureID1 = 0;
unsigned int g_uiTextureID2 = 0;
unsigned int g_uiTextureID3 = 0;
unsigned int g_uiTextureID4 = 0;

bool Init ()
{
	glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
	glShadeModel (GL_FLAT);

	// 03/10/2004 - Loading of a rectangle TGA image
	{
		gtl::CImageTGA Image ("./data/image24_rec.tga");
		glGenTextures (1, &g_uiTextureID1);
		glBindTexture (GL_TEXTURE_RECTANGLE_ARB, g_uiTextureID1);
		glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, 3, Image.Width (), Image.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image.Data ());
	}

	// 03/10/2004 - Loading of a square TGA image
	{
		gtl::CImageTGA Image ("./data/image24.tga");
		glGenTextures (1, &g_uiTextureID2);
		glBindTexture (GL_TEXTURE_2D, g_uiTextureID2);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D (GL_TEXTURE_2D, 0, 3, Image.Width (), Image.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image.Data ());
	}

	// 03/10/2004 - Loading of a square BMP image
	{
		gtl::CImageBMP Image ("./data/image24.bmp");
		glGenTextures (1, &g_uiTextureID3);
		glBindTexture (GL_TEXTURE_2D, g_uiTextureID3);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D (GL_TEXTURE_2D, 0, 3, Image.Width (), Image.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Image.Data ());
	}

	// 03/10/2004 - Loading of a square RAW image
	{
		gtl::CImageRAW Image ("./data/image24.raw", 64, 64, 24);
		glGenTextures (1, &g_uiTextureID4);
		glBindTexture (GL_TEXTURE_2D, g_uiTextureID4);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D (GL_TEXTURE_2D, 0, 3, Image.Width (), Image.Height (), 0, GL_RGB, GL_UNSIGNED_BYTE, Image.Data ());
	}

	return true;
}

void Draw ()
{
	glClear (GL_COLOR_BUFFER_BIT);

	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();
		glLoadIdentity ();
		glOrtho (0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
		glMatrixMode (GL_MODELVIEW);

		// Rendering of the rectangle texture.
		glEnable (GL_TEXTURE_RECTANGLE_ARB);
			// Image on corner down right
			glLoadIdentity ();
			glTranslated (WINDOW_WIDTH - 192.0f, 0.0f,  0.0f);
			glBindTexture (GL_TEXTURE_RECTANGLE_ARB, g_uiTextureID1);
			glBegin (GL_QUADS);
				glTexCoord2f ( 0.0f,  0.0f); glVertex2f (  0.0f,  0.0f);
				glTexCoord2f (64.0f,  0.0f); glVertex2f (192.0f,  0.0f);
				glTexCoord2f (64.0f, 48.0f); glVertex2f (192.0f,144.0f);
				glTexCoord2f ( 0.0f, 48.0f); glVertex2f (  0.0f,144.0f);
			glEnd ();
		glDisable (GL_TEXTURE_RECTANGLE_ARB);

		// Rendering of 2D textures.
		glEnable (GL_TEXTURE_2D);
			// Image on corner down left
			glLoadIdentity ();
			glTranslated (0.0f, 0.0f,  0.0f);
			glBindTexture (GL_TEXTURE_2D, g_uiTextureID2);
			glBegin (GL_QUADS);
				glTexCoord2f (0.0f, 1.0f); glVertex2f (  0.0f,   0.0f);
				glTexCoord2f (1.0f, 1.0f); glVertex2f (192.0f,   0.0f);
				glTexCoord2f (1.0f, 0.0f); glVertex2f (192.0f, 192.0f);
				glTexCoord2f (0.0f, 0.0f); glVertex2f (  0.0f, 192.0f);
			glEnd ();

			// Image on corner up left
			glLoadIdentity ();
			glTranslated (0.0f, WINDOW_HEIGHT - 192.0f,  0.0f);
			glBindTexture (GL_TEXTURE_2D, g_uiTextureID3);
			glBegin (GL_QUADS);
				glTexCoord2f (0.0f, 0.0f); glVertex2f (  0.0f,   0.0f);
				glTexCoord2f (1.0f, 0.0f); glVertex2f (192.0f,   0.0f);
				glTexCoord2f (1.0f, 1.0f); glVertex2f (192.0f, 192.0f);
				glTexCoord2f (0.0f, 1.0f); glVertex2f (  0.0f, 192.0f);
			glEnd ();

			// Image on corner up right
			glLoadIdentity ();
			glTranslated (WINDOW_WIDTH - 192.0f, WINDOW_HEIGHT - 192.0f,  0.0f);
			glBindTexture (GL_TEXTURE_2D, g_uiTextureID4);
			glBegin (GL_QUADS);
				glTexCoord2f (0.0f, 0.0f); glVertex2f (  0.0f,   0.0f);
				glTexCoord2f (1.0f, 0.0f); glVertex2f (192.0f,   0.0f);
				glTexCoord2f (1.0f, 1.0f); glVertex2f (192.0f, 192.0f);
				glTexCoord2f (0.0f, 1.0f); glVertex2f (  0.0f, 192.0f);
			glEnd ();
		glDisable (GL_TEXTURE_2D);

		glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
	glMatrixMode (GL_MODELVIEW);

	glFlush ();
}

void End ()
{
	// Free textures objects
	glDeleteTextures (1, &g_uiTextureID1);
	glDeleteTextures (1, &g_uiTextureID2);
	glDeleteTextures (1, &g_uiTextureID3);
	glDeleteTextures (1, &g_uiTextureID4);
}

