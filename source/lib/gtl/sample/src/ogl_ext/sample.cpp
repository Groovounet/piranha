/***********************************************\
	GTL sample : Extensions
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	sample.cpp, 03/10/2004
\***********************************************/

#include "./timer.h"
#include "./sample.h"
#include <fstream>

#define MOVE_X			10
#define MOVE_Y			16

#define CHECK(Position) (((Position) < 360) && ((Position) > -MOVE_Y))

int g_iAddPosition = 0;

gtl::CFontTGA g_Text;
CTimerSDL g_Timer;

short iFpsBuffer = 0, iFps = 0;

char* pVendor;
char* pRenderer;
char* pVersionGL;
char* pExtensionsGL;
char* pVersionGLU;
char* pExtensionsGLU;

void AfficheEXT()
{
	while(*pExtensionsGL)
	{
		if(*pExtensionsGL==' ')
			putchar ('\n');
		else
			putchar (*pExtensionsGL);
		*pExtensionsGL++;
	}
}

void SaveExtensions (const char* pExtension, std::ofstream & FileOut)
{
	while(*pExtension)
	{
		if(*pExtension==' ')
			FileOut << "\n";
		else
			FileOut << *pExtension;
		*pExtension++;
	}
}

void CompteFPS ()
{
	iFpsBuffer++;
	
	if (g_Timer.GetTime () >= 1.0f)
	{
		iFps = iFpsBuffer;
		iFpsBuffer = 0;
		g_Timer.Init ();
	}
	
	g_Text.Print (WINDOW_WIDTH - 128, WINDOW_HEIGHT - 32, "%d fps", iFps);
}

void DisplayExtension (char *pExt, int & iPosition)
{
	int x = 16;
	while (*pExt)
	{
		if (*pExt==' ')
		{
			iPosition -= MOVE_Y;
			x = 16;
		}
		else
		{
			if (CHECK (iPosition))
			{
				g_Text.Print (x, iPosition, "%c", *pExt);
				x += MOVE_X;
			}
		}
		*pExt++;
	}
}

bool Init ()
{
	g_Timer.Init ();

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth (1.0f);

	pVendor = (char *) glGetString (GL_VENDOR);
	pRenderer = (char *) glGetString (GL_RENDERER);
	pVersionGL = (char *) glGetString (GL_VERSION);
	pExtensionsGL = (char *) glGetString (GL_EXTENSIONS);
	pVersionGLU = (char *) gluGetString (GLU_VERSION);
	pExtensionsGLU = (char *) gluGetString (GLU_EXTENSIONS);

	char* pCarte = pRenderer;
	int iBoardNameSize = 0;
	bool bContinu = true;
	while(*pCarte && bContinu)
	{
		if(*pCarte=='/')
			bContinu = false;

		iBoardNameSize++;
		*pCarte++;
	}

	char *szFileName = new char [iBoardNameSize];
	int i;
	for (i = 0; i < (iBoardNameSize-1); i++)
		szFileName[i] = pRenderer[i];

	szFileName[i] = '\0';

	std::ofstream FileOut ((std::string (szFileName) + std::string (".txt")).c_str ());

	FileOut << "Fabriquant : " << pVendor << "\n";
	FileOut << "Carte et Rendu : " << pRenderer << "\n";
	FileOut << "Version d'OpenGL :" << pVersionGL << "\n\n";
	
	FileOut << "Liste des extensions OpenGL :" << "\n";
	SaveExtensions (pExtensionsGL, FileOut);

	FileOut << "\n";
	FileOut << "Version de GLU :" << pVersionGLU << "\n";

	FileOut << "Liste des extensions GLU :" << "\n";
	SaveExtensions (pExtensionsGLU, FileOut);

	FileOut << std::endl;

	FileOut.close();

    g_Text.Load ("./data/font1.tga");
	g_Text.Enable (gtl::FONT_SCALE);
	g_Text.Color (1.0f, 1.0f, 1.0f);
    g_Text.Size (12, 16);

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
		glLoadIdentity ();
		glPushMatrix ();

		g_Text.Spacing (16);
		g_Text.Begin ();
			g_Text.Print (16, WINDOW_HEIGHT - 32, WINDOW_NAME);
			g_Text.Print (16, 32, "G-Truc Creation (www.g-truc.net)");
			g_Text.Print (160, 16, "Par Groove (groove@g-truc.net)");

			CompteFPS ();
		g_Text.End ();

		glPushAttrib (GL_ALL_ATTRIB_BITS);
			glViewport (0, 64, WINDOW_WIDTH, WINDOW_HEIGHT - 128);
			glMatrixMode (GL_PROJECTION);
			glLoadIdentity ();
			glOrtho (0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT - 128, -1.0f, 1.0f);
			glMatrixMode (GL_MODELVIEW);
			glLoadIdentity ();

			glBegin (GL_QUADS);
				glColor3f (0.05f, 0.05f, 0.05f);
				glVertex2f (0, 0);
				glVertex2f (0, WINDOW_HEIGHT);
				glVertex2f (WINDOW_WIDTH, WINDOW_HEIGHT);
				glVertex2f (WINDOW_WIDTH, 0);
			glEnd ();

			g_Text.Spacing (10);
			g_Text.Enable (gtl::FONT_BLEND);

			g_Text.Begin ();
				int iPosition = WINDOW_WIDTH / 2 - g_iAddPosition;

				if (CHECK (iPosition))
					g_Text.Print (16, iPosition, "Fabricant : %s", pVendor);
				iPosition -= MOVE_Y;

				if (CHECK (iPosition))
					g_Text.Print (16, iPosition, "Carte Graphique : %s", pRenderer);
				iPosition -= MOVE_Y;

				if (CHECK (iPosition))
					g_Text.Print (16, iPosition, "Version d'OpenGL : %s", pVersionGL);
				iPosition -= MOVE_Y;

				if (CHECK (iPosition))
					g_Text.Print (16, iPosition, "Extensions de GL :");
				iPosition -= MOVE_Y;
				DisplayExtension (pExtensionsGL, iPosition);

				if (CHECK (iPosition))
					g_Text.Print (16, iPosition, "Version de GLU : %s", pVersionGLU);
				iPosition -= MOVE_Y;

				if (CHECK (iPosition))
					g_Text.Print (16, iPosition, "Extensions de GLU :");
				iPosition -= MOVE_Y;
				DisplayExtension (pExtensionsGLU, iPosition);
			g_Text.End ();

			g_Text.Disable (gtl::FONT_BLEND);
		glPopAttrib ();

		glPopMatrix ();
		
		glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
	glMatrixMode (GL_MODELVIEW);
}

void End ()
{

}
