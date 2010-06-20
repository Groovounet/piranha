/***********************************************\
	GTL sample : frustum culling
	Copyright (c) 2003-2004, G-Truc Creation
*************************************************
	G-Truc Creation, www.g-truc.net
	par Groove, groove@g-truc.net
*************************************************
	sample.cpp, 08/11/2004
\***********************************************/

#include "./sample.h"
#include <stdio.h>

gtl::CCamera *g_pCamera = 0;
gtl::CFontTGA *g_pFont = 0;
unsigned int g_uiSpriteID = 0;

bool g_bDoFrustumCulling = true;
float fAngle;

unsigned int g_iFps = 0;
unsigned int g_iFpsCount = 0;
time_t g_TempsStart = 0;

bool g_bMoveForward = false;
bool g_bMoveBackward = false;
bool g_bMoveRight = false;
bool g_bMoveLeft = false;

SObjectData g_Objects[NUM_OBJECTS];

PFNGLPOINTPARAMETERFARBPROC		glPointParameterfARB	= 0;
PFNGLPOINTPARAMETERFVARBPROC	glPointParameterfvARB	= 0;

void FPS_Count ()
{
	g_iFpsCount++;
	if (time (NULL) - g_TempsStart > 0)
	{
		g_iFps = g_iFpsCount;
		g_TempsStart = time (NULL);
		g_iFpsCount = 0;
	}
}

void KeyboardDown (int iKey)
{
	if (iKey == SDLK_KP8)
		g_bMoveForward = true;

	if (iKey == SDLK_KP2)
		g_bMoveBackward = true;

	if (iKey == SDLK_KP6)
		g_bMoveRight = true;

	if (iKey == SDLK_KP4)
		g_bMoveLeft = true;
}

void KeyboardUp (int iKey)
{
	if (iKey == SDLK_ESCAPE)
		exit (0);

	if (iKey == SDLK_KP8)
		g_bMoveForward = false;

	if (iKey == SDLK_KP2)
		g_bMoveBackward = false;

	if (iKey == SDLK_KP6)
		g_bMoveRight = false;

	if (iKey == SDLK_KP4)
		g_bMoveLeft = false;

	if (iKey == SDLK_c)
		g_bDoFrustumCulling = !g_bDoFrustumCulling;
}

void PointSprite_Init ()
{
	char *ext = (char*)glGetString (GL_EXTENSIONS);

	if (strstr (ext, "GL_ARB_point_parameters"))
	{
		glPointParameterfARB = (PFNGLPOINTPARAMETERFARBPROC) SDL_GL_GetProcAddress ("glPointParameterfARB");
		glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC) SDL_GL_GetProcAddress ("glPointParameterfvARB");

		if (!glPointParameterfARB || !glPointParameterfvARB)
			return;
	}

	gtl::CImageTGA Image ("./data/particle.tga");
	glGenTextures (1, &g_uiSpriteID);
	glBindTexture (GL_TEXTURE_2D, g_uiSpriteID);
	glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, 3, Image.Width (), Image.Height (), 0, GL_RGB, GL_UNSIGNED_BYTE, Image.Data ());
}

bool Begin ()
{
    g_pCamera = new gtl::CCamera;
    g_pCamera->SetViewDistance (32.f);
	g_pCamera->Enable (gtl::CAMERA_FRUSTUM);

    g_pFont = new gtl::CFontTGA;
	g_pFont->Load ("./data/font3.tga");
    g_pFont->Enable (gtl::FONT_BLEND | gtl::FONT_SCALE);
	g_pFont->Color (1.0f, 1.0f, 1.0f);
    g_pFont->Size (8, 16); 

	glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc (GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	float fMaxSize = 0.0f;
	glGetFloatv (GL_POINT_SIZE_MAX_ARB, &fMaxSize);
    PointSprite_Init ();

	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		g_Objects[i].Coord (gtl::X) = gtl::CRand::Float (-64.f, 64.f);
		g_Objects[i].Coord (gtl::Y) = gtl::CRand::Float (-64.f, 64.f);
		g_Objects[i].Coord (gtl::Z) = gtl::CRand::Float (-64.f, 64.f);

		g_Objects[i].Color (gtl::X) = gtl::CRand::Float (0.5f, 1.0f);
		g_Objects[i].Color (gtl::Y) = gtl::CRand::Float (0.5f, 1.0f);
		g_Objects[i].Color (gtl::Z) = gtl::CRand::Float (0.5f, 1.0f);

		g_Objects[i].fRadius = gtl::CRand::Float (fMaxSize * 0.5f, fMaxSize);
	}

    return true;
}

void End ()
{
    if (g_pCamera)
        delete g_pCamera;
    if (g_pFont)
        delete g_pFont;
}

void Draw ()
{
	if (g_bMoveForward)
		g_pCamera->Move (MOVE_SPEED);
	if (g_bMoveBackward)
		g_pCamera->Move (-MOVE_SPEED);
	if (g_bMoveRight)
		g_pCamera->Strafe (MOVE_SPEED);
	if (g_bMoveLeft)
		g_pCamera->Strafe (-MOVE_SPEED);

	int iObjectNbr = 0;

	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity ();

	int iMousePosX, iMousePosY;
	unsigned short unMiddleX = 640 >> 1;
	unsigned short unMiddleY = 480 >> 1;

	SDL_GetMouseState (&iMousePosX, &iMousePosY);
	SDL_WarpMouse (unMiddleX, unMiddleY);

	g_pCamera->LookAt ((float)(unMiddleX - iMousePosX), (float)(unMiddleY - iMousePosY));

	glPushAttrib (GL_ALL_ATTRIB_BITS);
	glPushMatrix ();
		glEnable (GL_TEXTURE_2D);
		glEnable (GL_POINT_SPRITE_ARB);
		glEnable (GL_BLEND);

		float fQuadratic[] =  {0.0001f, 0.0001f, 0.0001f};
		glPointParameterfvARB (GL_POINT_DISTANCE_ATTENUATION_ARB, fQuadratic);

		glPointParameterfARB (GL_POINT_FADE_THRESHOLD_SIZE_ARB, 1.f);
		glPointParameterfARB (GL_POINT_SIZE_MIN_ARB, 1.f);

		glBindTexture (GL_TEXTURE_2D, g_uiSpriteID);
		glTexEnvf (GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);

		glBegin (GL_POINTS);

			if (g_bDoFrustumCulling)
			{
				for (int i=0; i<NUM_OBJECTS; i++)
				{
					if (g_pCamera->IsInFrustum (g_Objects[i].Coord))
					{
						glPointParameterfARB (GL_POINT_SIZE_MAX_ARB, g_Objects[i].fRadius);
						glColor3fv (g_Objects[i].Color);
						glVertex3fv (g_Objects[i].Coord);
					}
					else
						iObjectNbr++;
				}
			}
			else
			{
				for (int i=0; i<NUM_OBJECTS; i++)
				{
					glPointParameterfARB (GL_POINT_SIZE_MAX_ARB, g_Objects[i].fRadius);
					glColor3fv (g_Objects[i].Color);
					glVertex3fv (g_Objects[i].Coord);
				}
			}
		glEnd ();
	glPopMatrix ();
	glPopAttrib ();

	FPS_Count ();

	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();
		glLoadIdentity ();
		glOrtho (0,640,0,480,-1,1);
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		
		glPushMatrix ();
			g_pFont->Begin ();
			    g_pFont->Print (0, 8, "Utiliser la touche \'c\' pour activer ou non le fustrum culling");
   			    g_pFont->Print (0, 24, "Nombre d'objets masques = %d (sur %d)", iObjectNbr, NUM_OBJECTS);
				g_pFont->Print (0, 40, "%d FPS", g_iFps);
			g_pFont->End ();
		glPopMatrix ();
		
		glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
	glMatrixMode (GL_MODELVIEW);
}

