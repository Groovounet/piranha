//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 30-12-2004
//! \file ./piranha/terrain/ground.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./ground.h"
#include "../file/index.h"
#include "../gl/camera.h"
#include "../gl/proc.h"
#include "../gl/state_auto.h"

using namespace terrain;

static const char*      TEXTURE_PLANT =             "./data/terrain/plant.tga";

const char g_cFanCode [16] = 
{
	10,  8,  8, 12,
	 8,  0, 12, 14,
	 8, 12,  0, 14,
	12, 14, 14,  0
};

const EQuadNode g_FanStart [16] = 
{
	QUAD_NODE_UR, QUAD_NODE_UR, QUAD_NODE_LR, QUAD_NODE_UR,
	QUAD_NODE_LL, QUAD_NODE_LR, QUAD_NODE_LR, QUAD_NODE_UR,
	QUAD_NODE_UL, QUAD_NODE_UL, QUAD_NODE_LR, QUAD_NODE_UL,
	QUAD_NODE_LL, QUAD_NODE_LL, QUAD_NODE_LR, QUAD_NODE_LR
};

#define FRUSTUM_CULLING_BUG_FIXE	m_fScale * m_fDetailmapRepeat

CGround::CGround (const file::SGround * pGround, const file::SPlants * pPlants, const file::SWater * pWater)
{
    m_pucQuadMatrix = 0;
    m_fMinResolution = pGround->m_fResolutionMin;//2;
    m_fDesiredResolution = pGround->m_fResolutionDesired;//12;
    m_fScale = /*pGround->m_fScale; */ 0.5f;
    m_fDetailmapRepeat = pGround->m_fDetailmapRepeat;
    m_fPlantLodDistance = pPlants->m_fLodDistance;
    m_fPlantHeightMax = pPlants->m_fHeightMax;
    m_fPlantHeightMin = pPlants->m_fHeightMin;
    m_pNormal = 0;
    m_pPlantTex = 0;
    m_pPlant = 0;

    _Load (pGround, pPlants, pWater);
}

CGround::~CGround ()
{
    if (m_pNormal)
        delete [] m_pNormal;
    if (m_pucQuadMatrix)
        delete [] m_pucQuadMatrix;
    if (m_pfHeightmap)
        delete [] m_pfHeightmap;
    if (m_pfHeightmapBase)
        delete [] m_pfHeightmapBase;
    if (m_pPlant)
        delete [] m_pPlant;

    file::CManager* pManager = file::CManager::Instance ();
    pManager->DeleteTexture2D (m_pGroundGood);
    pManager->DeleteTexture2D (m_pGroundDark);
    pManager->DeleteTexture2D (m_pDetailmap);
    pManager->DeleteTexture2D (m_pLightmap);
    pManager->DeleteTexture2D (m_pPlantTex);

    delete m_pShader;
}

void CGround::Render () const
{
    glPushAttrib (GL_ALL_ATTRIB_BITS);
    glPushMatrix ();

    glEnable (GL_CULL_FACE);

    glTranslated (-m_unSize / 2, -m_unSize / 2, 0);

    m_pShader->Enable ();

    glActiveTextureARB (GL_TEXTURE0_ARB);
    m_pGroundGood->Bind ();
    glActiveTextureARB (GL_TEXTURE1_ARB);
    m_pGroundDark->Bind ();
    glActiveTextureARB (GL_TEXTURE2_ARB);
    m_pDetailmap->Bind ();
    glActiveTextureARB (GL_TEXTURE3_ARB);
    m_pLightmap->Bind ();

	if (m_uiVarColorMapGood != -1)
		glUniform1iARB (m_uiVarColorMapGood, 0);
	if (m_uiVarColorMapDark != -1)
		glUniform1iARB (m_uiVarColorMapDark, 1);
	if (m_uiVarDetailMap != -1)
		glUniform1iARB (m_uiVarDetailMap, 2);
	if (m_uiVarLightMap != -1)
		glUniform1iARB (m_uiVarLightMap, 3);

    unsigned short unCenter = (m_unSize - 1) / 2;
    _RenderNode (unCenter, unCenter, m_unSize);

    m_pShader->Disable ();

    glDisable (GL_CULL_FACE);

    _RenderPlants ();

    glPopMatrix ();
    glPopAttrib ();
}

void CGround::Update ()
{
    _BuildQuadMatrix ();
}

float CGround::Distort (int x, int y)
{
    x += m_unSize / 2;
    y += m_unSize / 2;

	float fFilterData[7][7] = 
	{
        {0.0f, 0.0f, 0.5f, 0.6f, 0.5f, 0.0f, 0.0f},
        {0.0f, 1.1f, 1.2f, 1.4f, 1.2f, 1.1f, 0.0f},
		{0.5f, 1.3f, 1.7f, 1.8f, 1.7f, 1.3f, 0.5f},
        {0.6f, 1.4f, 1.8f, 2.0f, 1.8f, 1.4f, 0.6f},
        {0.5f, 1.3f, 1.7f, 1.8f, 1.7f, 1.3f, 0.5f},
        {0.0f, 1.1f, 1.2f, 1.4f, 2.0f, 1.1f, 0.0f},
        {0.0f, 0.0f, 0.5f, 0.6f, 0.5f, 0.0f, 0.0f},
	};

	for (int j = - 3; j <= 3; j++)
	{
        if (y + j < 0 || y + j >= m_unSize)
            continue;

        for (int i = - 3; i <= 3; i++)
		{
            if (x + i < 0 || x + i >= m_unSize)
                continue;

            m_pfHeightmap[(x + i) + (y + j) * m_unSize] -= fFilterData[j + 3][i + 3];
		}
	}

    return m_pfHeightmap[x + y * m_unSize];
}

void CGround::_RenderPlants () const
{
    gtl::CVector3<float> Camera = gl::CCamera::Instance ()->GetPosition () + gtl::CVector3<float> (m_unSize / 2.f, m_unSize / 2.f, 0);

    glActiveTextureARB (GL_TEXTURE0_ARB);
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_ALPHA_TEST);
    glAlphaFunc (GL_GREATER, 0.9f);

    for (std::list<SPlant>::const_iterator it = m_Plant.begin (); it != m_Plant.end (); it++)
    {
        gtl::CVector3<float> Position = it->m_Position;
        Position (gtl::Z) = m_pfHeightmap[(int)(it->m_Position (gtl::X) + it->m_Position (gtl::Y) * m_unSize)];

        if ((Position - Camera).Magnitude () > m_fPlantLodDistance)
            continue;

        it->m_pTexture->Bind ();
        glBegin (GL_QUADS);
            glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 0, 0);
            glVertex3f (it->m_Position (gtl::X) - cosf (it->m_fAngle) * 1.0f, it->m_Position (gtl::Y) - sinf (it->m_fAngle) * 1.0f, Position (gtl::Z) + 0.0f);
            glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 1, 0);
            glVertex3f (it->m_Position (gtl::X) + cosf (it->m_fAngle) * 1.0f, it->m_Position (gtl::Y) + sinf (it->m_fAngle) * 1.0f, Position (gtl::Z) + 0.0f);
            glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 1, 1);
            glVertex3f (it->m_Position (gtl::X) + cosf (it->m_fAngle) * 1.0f, it->m_Position (gtl::Y) + sinf (it->m_fAngle) * 1.0f, Position (gtl::Z) + 4.0f);
            glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 0, 1);
            glVertex3f (it->m_Position (gtl::X) - cosf (it->m_fAngle) * 1.0f, it->m_Position (gtl::Y) - sinf (it->m_fAngle) * 1.0f, Position (gtl::Z) + 4.0f);

            glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 0, 0);
            glVertex3f (it->m_Position (gtl::X) - sinf (it->m_fAngle) * 1.0f, it->m_Position (gtl::Y) - cosf (it->m_fAngle) * 1.0f, Position (gtl::Z) + 0.0f);
            glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 1, 0);
            glVertex3f (it->m_Position (gtl::X) + sinf (it->m_fAngle) * 1.0f, it->m_Position (gtl::Y) + cosf (it->m_fAngle) * 1.0f, Position (gtl::Z) + 0.0f);
            glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 1, 1);
            glVertex3f (it->m_Position (gtl::X) + sinf (it->m_fAngle) * 1.0f, it->m_Position (gtl::Y) + cosf (it->m_fAngle) * 1.0f, Position (gtl::Z) + 4.0f);
            glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 0, 1);
            glVertex3f (it->m_Position (gtl::X) - sinf (it->m_fAngle) * 1.0f, it->m_Position (gtl::Y) - cosf (it->m_fAngle) * 1.0f, Position (gtl::Z) + 4.0f);
        glEnd ();
    }

    glDisable (GL_ALPHA_TEST);
    glDisable (GL_TEXTURE_2D);
}

bool CGround::_Load (const file::SGround * pGround, const file::SPlants * pPlants, const file::SWater * pWater)
{
	if (!_LoadHeightmap (pGround))
        return false;
    _NormalCalculation ();
    if (!_LoadTextures (pGround, pPlants))
        return false;
    if (!_LoadPlants (pPlants, pWater))
        return false;
    if (!_LoadShaders (pGround))
        return false;
    return true;
}

bool CGround::_LoadPlants (const file::SPlants * pPlants, const file::SWater * pWater)
{
    m_iPlant = pPlants->m_iPlants;
    m_pPlant = new SPlant [m_iPlant];
    for (int i = 0; i < pPlants->m_iPlants; i++)
    {
        SPlant Plant;
        int x;
        int y;
        float z;
        do
        {
            x = gtl::CRand::Int (0, m_unSize);
            y = gtl::CRand::Int (0, m_unSize);
            z = m_pfHeightmap[m_unSize * y + x];
        }
        while (z < m_fPlantHeightMin || z > m_fPlantHeightMax);
        Plant.m_Position = gtl::CVector3<float> ((float)x, (float)y, z);
        Plant.m_pTexture = m_pPlantTex;
        Plant.m_fAngle = gtl::CRand::Float (0, 360.f);
        m_Plant.push_back (Plant);
    }

    return true;
}

bool CGround::_LoadShaders (const file::SGround * pGround)
{
    m_pShader = new gl::CShader;

    if (!m_pShader->Load (pGround->m_szShaderVertex.c_str (), pGround->m_szShaderFragment.c_str ()))
        return false;
    m_uiVarColorMapGood = m_pShader->Uniform ("ColorMapGood");
    m_uiVarColorMapDark = m_pShader->Uniform ("ColorMapEvil");
    m_uiVarDetailMap = m_pShader->Uniform ("DetailMap");
    m_uiVarLightMap = m_pShader->Uniform ("LightMap");
    m_uiVarDistortion = m_pShader->Attrib ("Distortion");
    m_uiVarDistance = m_pShader->Attrib ("Distance");
    return true;
}

bool CGround::_LoadHeightmap (const file::SGround * pGround)
{
    gtl::CImageTGA HeightMap (pGround->m_szHeightmap.c_str ());
	m_unSize = HeightMap.Width ();

    unsigned char* pucHeightmap = new unsigned char [m_unSize * m_unSize];

    for (int j = 0; j < m_unSize; j++)
        for (int i = 0; i < m_unSize; i++)
            pucHeightmap[m_unSize * j + i] = HeightMap.Data () [m_unSize * 3 * j + (i * 3)];

	float fColor;

	float fFilterData[3][3] = 
	{
		{1.0, 2.0, 1.0},
		{2.0, 8.0, 2.0},
		{1.0, 2.0, 1.0}
	};

	float fFilterDiv = 20.0;

    m_pfHeightmap = new float [m_unSize * m_unSize];
    m_pfHeightmapBase = new float [m_unSize * m_unSize];

	for (int vy = 1; vy < m_unSize - 1; vy++)
	{
		for (int vx = 1; vx < m_unSize - 1; vx++)
		{
            fColor = 0.f;

			for (int j = -1; j <= 1; j++)
				for (int i = -1; i <= 1; i++)
					fColor += pucHeightmap[(vx + i) + m_unSize * (vy + j)] * fFilterData[j + 1][i + 1];

			fColor /= fFilterDiv;
			fColor = (fColor > 255.f) ? 255.f : ((fColor < 0.f) ? 0.f : fColor);
			
			m_pfHeightmap[vx + m_unSize * vy] = fColor * m_fScale;
//			m_pfHeightmap[vx + m_unSize * vy] = pucHeightmap[vx + m_unSize * vy] * m_fScale;
		}
	}

    memcpy (m_pfHeightmapBase, m_pfHeightmap, m_unSize * m_unSize * sizeof (float));

    //12-09-2004 TEST : heightmap distortion
    for (int j = 0; j < m_unSize; j++)
        for (int i = 0; i < m_unSize; i++)
            if (m_pfHeightmap[m_unSize * j + i] > 192)
                m_pfHeightmap[m_unSize * j + i] = 255;

    delete [] pucHeightmap;

	return true;
}

bool CGround::_LoadTextures (const file::SGround * pGround, const file::SPlants * pPlants)
{
    file::CManager* pManager = file::CManager::Instance ();
    m_pGroundGood = pManager->CreateTexture2D (pGround->m_szColormapGood.c_str ());
    m_pGroundDark = pManager->CreateTexture2D (pGround->m_szColormapEvil.c_str ());
    m_pDetailmap = pManager->CreateTexture2D (pGround->m_szDetailmap.c_str ());
    m_pLightmap = pManager->CreateTexture2D (pGround->m_szLightmap.c_str ());

    //for (std::list<SPlant>::iterator it = pPlants->m_Plant.begin (), int i = 0; it != pPlants->m_Plant.end (); it++, i++)
        m_pPlantTex = pManager->CreateTexture2D (TEXTURE_PLANT);

	return true;
}

// Method from "Game Programming Gems 3" by Jason Shankel in the gem named "Fast Heightfield normal calculation". Too easy ! :D
void CGround::_NormalCalculation ()
{
	if (!m_pNormal)
    {
        m_pNormal = new gtl::CVector3<float> [m_unSize * m_unSize];
        memset (m_pNormal, 0, m_unSize * m_unSize * sizeof (gtl::CVector3<float>));
    }

	for (int y = 1; y < (m_unSize - 1); y++)
	{
		for (int x = 1; x < (m_unSize - 1); x++)
		{
            float fH1 = m_pfHeightmap[(x + 1) + (y + 0) * m_unSize];
            float fH2 = m_pfHeightmap[(x + 0) + (y + 1) * m_unSize];
            float fH3 = m_pfHeightmap[(x - 1) + (y + 0) * m_unSize];
            float fH4 = m_pfHeightmap[(x + 0) + (y - 1) * m_unSize];
			m_pNormal [x + y * m_unSize] = gtl::CVector3<float> (fH3 - fH1, fH4 - fH2, 2).Normalize ();
        }
	}   
}

unsigned char CGround::_GetQuadMatrixData (int x, int y) const
{
    return m_pucQuadMatrix[y * m_unSize + x];
}

void CGround::_SubdivideNode (unsigned short x, unsigned short y, unsigned short unEdgeLength)
{
    unsigned char ucSubdivide = 0;
    gtl::CVector3<float> PositionCamera = gl::CCamera::Instance ()->GetPosition () - gtl::CVector3<float> (-m_unSize / 2.f, -m_unSize / 2.f, 0.f);

	float fHeight = m_pfHeightmap[(int)(x + y * m_unSize)];

	float fViewDistance = sqrt (SQR(PositionCamera (gtl::X) - x) + SQR(PositionCamera (gtl::Y) - y) + SQR(PositionCamera (gtl::Z) - fHeight));
	float f = fViewDistance / (unEdgeLength * m_fMinResolution * MAX(m_fDesiredResolution*_GetQuadMatrixData (x - 1, y) / 3, 1.0f));

	if (f<1.0f)
		ucSubdivide = 1;
		
	m_pucQuadMatrix [x + y * m_unSize] = ucSubdivide;
	
	if (ucSubdivide)
	{
		if (!(unEdgeLength<=3))
		{
			unsigned short unChildOffset = (unEdgeLength - 1) >> 2;
			unsigned short unChildEdgeLength = (unEdgeLength+1) >> 1;

			_SubdivideNode (x - unChildOffset, y - unChildOffset, unChildEdgeLength);
			_SubdivideNode (x + unChildOffset, y - unChildOffset, unChildEdgeLength);
			_SubdivideNode (x - unChildOffset, y + unChildOffset, unChildEdgeLength);
			_SubdivideNode (x + unChildOffset, y + unChildOffset, unChildEdgeLength);
		}
	} 
}

void CGround::_BuildQuadMatrix ()
{
	unsigned short unCenter = (m_unSize - 1) / 2;
	
	if (m_pucQuadMatrix == 0)
		m_pucQuadMatrix = new unsigned char [m_unSize * m_unSize];

	for (int i = 0; i< (m_unSize*m_unSize); i++)
		m_pucQuadMatrix[i] = 1;

	_SubdivideNode (unCenter, unCenter, m_unSize);
}

void CGround::_RenderVertex (float x, float y, float u, float v) const
{
	float fHeightModified = m_pfHeightmap[(int)(x + y * m_unSize)];
    float fHeightBase = m_pfHeightmapBase[(int)(x + y * m_unSize)];
	gtl::CVector3<float> Normal = m_pNormal[(int)(x + y * m_unSize)];
	gtl::CVector3<float> Distance = gl::CCamera::Instance ()->GetPosition () - gtl::CVector3<float> (x - m_unSize / 2.f, y - m_unSize / 2.f, fHeightModified);

    glVertexAttrib1fARB (m_uiVarDistortion, fHeightModified - fHeightBase);
    glVertexAttrib1fARB (m_uiVarDistance, Distance.Magnitude ());
    glMultiTexCoord2fARB (GL_TEXTURE0_ARB, u, v);
	glMultiTexCoord2fARB (GL_TEXTURE1_ARB, u, v);
	glMultiTexCoord2fARB (GL_TEXTURE2_ARB, u * m_fDetailmapRepeat, v * m_fDetailmapRepeat);
	glMultiTexCoord2fARB (GL_TEXTURE3_ARB, u, v);
	glNormal3fv (Normal);
	glVertex3f (x, y, fHeightModified);
}

#define RENDER_MODE GL_TRIANGLE_FAN //GL_TRIANGLE_FAN GL_LINE_STRIP

void CGround::_RenderNode (float x, float y, int iEdgeLength) const
{
	int iFanCode;
	int iChildEdgeLength;
	int iFanLength;
	int iFanPosition;

	int iX = (int) x;
	int iY = (int) y;

	float fEdgeOffset = (iEdgeLength - 1.0f) / 2.0f;

    //12-18-2004 - FIX : This function allow frustum culling but it don't work.
    //if (!gl::CCamera::Instance ()->IsInFrustum (x/* - m_unSize / 2.f*/, y/* - m_unSize / 2.f*/, z * m_fScale, fEdgeOffset/* * FRUSTUM_CULLING_BUG_FIXE*/))
    //    return;

	int iAdjOffset = iEdgeLength-1;
	float fTexLeft =    ((float) fabs (x-fEdgeOffset) / (m_unSize-1));
	float fTexBottom =  ((float) fabs (y-fEdgeOffset) / (m_unSize-1));
	float fTexRight =   ((float) fabs (x+fEdgeOffset) / (m_unSize-1));
	float fTexTop	=   ((float) fabs (y+fEdgeOffset) / (m_unSize-1));

    float fMidX = ((fTexLeft + fTexRight) / 2.0f);
	float fMidY = ((fTexBottom + fTexTop) / 2.0f);

	if (_GetQuadMatrixData (iX, iY))
	{
		if (iEdgeLength<=3)
		{
			glBegin (RENDER_MODE);
            //glBegin (GL_QUADS);
            //glBegin (GL_LINE_STRIP);
				_RenderVertex (x, y, fMidX, fMidY);
				
				_RenderVertex (x-fEdgeOffset, y-fEdgeOffset, fTexLeft, fTexBottom);

				if (((iY-iAdjOffset)<0) || _GetQuadMatrixData (iX, iY-iAdjOffset))
					_RenderVertex (x, y-fEdgeOffset, fMidX, fTexBottom);

				_RenderVertex (x+fEdgeOffset, y-fEdgeOffset, fTexRight, fTexBottom);

				if (((iX+iAdjOffset)>=m_unSize) || _GetQuadMatrixData (iX+iAdjOffset, iY))
					_RenderVertex (x+fEdgeOffset, y, fTexRight, fMidY);

				_RenderVertex (x+fEdgeOffset, y+fEdgeOffset, fTexRight, fTexTop);

				if (((iY+iAdjOffset)>=m_unSize) || _GetQuadMatrixData (iX, iY+iAdjOffset))
					_RenderVertex( x, y+fEdgeOffset, fMidX, fTexTop);

				_RenderVertex( x-fEdgeOffset, y+fEdgeOffset, fTexLeft, fTexTop );

				if (((iX-iAdjOffset)<0) || _GetQuadMatrixData (iX-iAdjOffset, iY))
					_RenderVertex( x-fEdgeOffset, y, fTexLeft, fMidY );

				_RenderVertex (x-fEdgeOffset, y-fEdgeOffset, fTexLeft, fTexBottom);
			glEnd ();
			return;
		}
		else
		{
			int iChildOffset = (iEdgeLength-1) / 4;
			float fChildOffset = (float)iChildOffset;

			iChildEdgeLength = (iEdgeLength+1)/2;

			iFanCode =  (_GetQuadMatrixData (iX+iChildOffset, iY+iChildOffset)) * 8;
			iFanCode |= (_GetQuadMatrixData (iX-iChildOffset, iY+iChildOffset)) * 4;
			iFanCode |= (_GetQuadMatrixData (iX-iChildOffset, iY-iChildOffset)) * 2;
			iFanCode |= (_GetQuadMatrixData (iX+iChildOffset, iY-iChildOffset));

			if (iFanCode == QUAD_NO_FAN)
			{
				_RenderNode (x-fChildOffset, y-fChildOffset, iChildEdgeLength);
				_RenderNode (x+fChildOffset, y-fChildOffset, iChildEdgeLength);
				_RenderNode (x-fChildOffset, y+fChildOffset, iChildEdgeLength);
				_RenderNode (x+fChildOffset, y+fChildOffset, iChildEdgeLength);
				return;
			}

			if (iFanCode == QUAD_LL_UR)
			{
				// 27/08/2003 - UR
				glBegin (RENDER_MODE);
					_RenderVertex (x, y, fMidX, fMidY);
					_RenderVertex (x+fEdgeOffset, y, fTexRight, fMidY);
					_RenderVertex (x+fEdgeOffset, y+fEdgeOffset, fTexRight, fTexTop);
					_RenderVertex (x, y+fEdgeOffset, fMidX, fTexTop);
				glEnd ();

				// 27/08/2003 - LL
				glBegin (RENDER_MODE);
					_RenderVertex (x, y, fMidX, fMidY);
					_RenderVertex (x-fEdgeOffset, y, fTexLeft, fMidY);
					_RenderVertex (x-fEdgeOffset, y-fEdgeOffset, fTexLeft, fTexBottom);
					_RenderVertex (x, y-fEdgeOffset, fMidX, fTexBottom);
				glEnd ();

				// 27/08/2003 - UL
				_RenderNode (x-fChildOffset, y+fChildOffset, iChildEdgeLength);
				// 27/08/2003 - LR
				_RenderNode (x+fChildOffset, y-fChildOffset, iChildEdgeLength);
				return;
			}

			if (iFanCode==QUAD_LR_UL)
			{
				// 27/08/2003 - UL
				glBegin (RENDER_MODE);
					_RenderVertex (x, y, fMidX, fMidY);
					_RenderVertex (x, y+fEdgeOffset, fMidX, fTexTop);
					_RenderVertex (x-fEdgeOffset, y+fEdgeOffset, fTexLeft, fTexTop);
					_RenderVertex (x-fEdgeOffset, y, fTexLeft, fMidY);
				glEnd ();

				// 27/08/2003 - LR
				glBegin (RENDER_MODE);
					_RenderVertex (x, y, fMidX, fMidY);
					_RenderVertex (x, y-fEdgeOffset, fMidX, fTexBottom);
					_RenderVertex (x+fEdgeOffset, y-fEdgeOffset, fTexRight, fTexBottom);
					_RenderVertex (x+fEdgeOffset, y, fTexRight, fMidY);
				glEnd ();

				// 27/08/2003 - UR
				_RenderNode (x+fChildOffset, y+fChildOffset, iChildEdgeLength);
				// Groove - 27/08/2003 - LL
				_RenderNode (x-fChildOffset, y-fChildOffset, iChildEdgeLength);
				return;
			}

			if (iFanCode==QUAD_COMPLETE_FAN)
			{
				glBegin (RENDER_MODE);
					_RenderVertex (x, y, fMidX, fMidY);

					_RenderVertex (x-fEdgeOffset, y-fEdgeOffset, fTexLeft, fTexBottom);

					if (((iY-iAdjOffset)<0) || _GetQuadMatrixData (iX, iY-iAdjOffset))
						_RenderVertex (x, y-fEdgeOffset, fMidX, fTexBottom);

					_RenderVertex (x+fEdgeOffset, y-fEdgeOffset, fTexRight, fTexBottom);

					if (((iX+iAdjOffset)>=m_unSize) || _GetQuadMatrixData (iX+iAdjOffset, iY))
						_RenderVertex (x+fEdgeOffset, y, fTexRight, fMidY );

					_RenderVertex (x+fEdgeOffset, y+fEdgeOffset, fTexRight, fTexTop);

					if (((iY+iAdjOffset)>=m_unSize) || _GetQuadMatrixData (iX, iY+iAdjOffset))
						_RenderVertex (x, y+fEdgeOffset, fMidX, fTexTop);

					_RenderVertex (x-fEdgeOffset, y+fEdgeOffset, fTexLeft, fTexTop);

					if (((iX-iAdjOffset)<0) || _GetQuadMatrixData (iX-iAdjOffset, iY))
						_RenderVertex (x-fEdgeOffset, y, fTexLeft, fMidY);

					_RenderVertex (x-fEdgeOffset, y-fEdgeOffset, fTexLeft, fTexBottom);
				glEnd ();
				return;
			}

			// 27/08/2003 - Triangle de jonctions de différentes tailles de triangles
			int iStart = g_FanStart[iFanCode];
			iFanLength = 0;

			// 27/08/2003 - Essayer (iFanLength<8)
			while (!(((long) g_cFanCode[iFanCode]) & (1<<iFanLength)) && (iFanLength<8))
				iFanLength++;

			glBegin (RENDER_MODE);
				_RenderVertex (x, y, fMidX, fMidY);

				for (iFanPosition=iFanLength; iFanPosition>0; iFanPosition--)
				{
					switch (iStart)
					{
					case QUAD_NODE_LR:
						if (((iY-iAdjOffset) < 0) || _GetQuadMatrixData (iX, iY-iAdjOffset) || (iFanPosition == iFanLength))
							_RenderVertex (x, y-fEdgeOffset, fMidX, fTexBottom);

						_RenderVertex (x+fEdgeOffset, y-fEdgeOffset, fTexRight, fTexBottom);

						if (iFanPosition == 1) 
							_RenderVertex (x+fEdgeOffset, y, fTexRight, fMidY);
						break;
					case QUAD_NODE_LL:
						if (((x-iAdjOffset) < 0) || _GetQuadMatrixData (iX-iAdjOffset, iY) || (iFanPosition == iFanLength))
							_RenderVertex (x-fEdgeOffset, y, fTexLeft, fMidY );

						_RenderVertex (x-fEdgeOffset, y-fEdgeOffset, fTexLeft, fTexBottom);

						if (iFanPosition == 1)
							_RenderVertex (x, y-fEdgeOffset, fMidX, fTexBottom);
						break;
					case QUAD_NODE_UL:
						if (((iY+iAdjOffset) >= m_unSize) || _GetQuadMatrixData (iX, iY+iAdjOffset) || (iFanPosition == iFanLength))
							_RenderVertex (x, y+fEdgeOffset, fMidX, fTexTop);

						_RenderVertex (x-fEdgeOffset, y+fEdgeOffset, fTexLeft, fTexTop);

						if (iFanPosition == 1)
							_RenderVertex (x-fEdgeOffset, y, fTexLeft, fMidY);
						break;
					case QUAD_NODE_UR:
						if (((iX+iAdjOffset) >= m_unSize) || _GetQuadMatrixData (iX+iAdjOffset, iY) || (iFanPosition == iFanLength))
							_RenderVertex (x+fEdgeOffset, y, fTexRight, fMidY);

						_RenderVertex (x+fEdgeOffset, y+fEdgeOffset, fTexRight, fTexTop);

						if (iFanPosition == 1)
							_RenderVertex (x, y+fEdgeOffset, fMidX, fTexTop);
						break;
					}

					iStart--;
					iStart &= 3;
				}
			glEnd ();

			// 27/08/2003 - Récurence de RenderNode () pour les carrés de jonctions
			for (iFanPosition = (4-iFanLength); iFanPosition>0; iFanPosition--)
			{
				switch (iStart)
				{
				case QUAD_NODE_LR:
					_RenderNode (x+fChildOffset, y-fChildOffset, iChildEdgeLength);
					break;
				case QUAD_NODE_LL:
					_RenderNode (x-fChildOffset, y-fChildOffset, iChildEdgeLength);
					break;
				case QUAD_NODE_UL:
					_RenderNode (x-fChildOffset, y+fChildOffset, iChildEdgeLength);
					break;
				case QUAD_NODE_UR:
					_RenderNode (x+fChildOffset, y+fChildOffset, iChildEdgeLength);
					break;
				}

				iStart--;
				iStart&= 3;
			}
			return;
		}
	}
}
