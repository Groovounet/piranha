#include "./terrain.h"

#define HEIGHT_DIV	4.f

CTerrain::CTerrain ()
{
	m_pucHeightmap = 0;
	m_pNormal = 0;
}

CTerrain::~CTerrain ()
{
	if (m_pucHeightmap)
		delete m_pucHeightmap;
	if (m_pNormal)
		delete m_pNormal;
}

bool CTerrain::Load (const char* szHeightmap, const char* szTexture)
{
	gtl::CImageTGA Heightmap (szHeightmap);
	if (!Heightmap.IsLoaded ())
		return false;

	m_unSize = Heightmap.Width ();
	m_pucHeightmap = new unsigned char[m_unSize * m_unSize];

	for (int i = 0; i < (m_unSize * m_unSize); i++)		
		m_pucHeightmap[i] = (Heightmap.Data ())[i*3];

	_NormalCalculation ();

	gtl::CImageTGA Texture (szTexture);
	if (!Texture.IsLoaded ())
		return false;

	glGenTextures (1, &m_uiTexture);
	glBindTexture (GL_TEXTURE_2D, m_uiTexture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, 3, Texture.Width (), Texture.Height (), 0, GL_BGR, GL_UNSIGNED_BYTE, Texture.Data ());

	return true;
}

void CTerrain::Draw () 
{
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_CULL_FACE);

	glBindTexture (GL_TEXTURE_2D, m_uiTexture);
	glPushMatrix ();
		for (int y=0; y<(m_unSize-1); y++)
		{
			glBegin (GL_TRIANGLE_STRIP);
				glColor4fv (gtl::CColor4<float>(1.0f, 1.0f, 1.0f, 1.0f));
				for (int x = 0; x < (m_unSize - 1); x++)
				{
					glTexCoord2f ((x + 0.0f) / m_unSize, (y + 1.0f) / m_unSize);
					glNormal3fv (m_pNormal[x + (y + 1) * m_unSize]);
					glVertex3i (x, y + 1, (int)(m_pucHeightmap[x + (y + 1) * m_unSize] / HEIGHT_DIV));

					glTexCoord2f ((x + 0.0f) / m_unSize, (y + 0.0f) / m_unSize);
					glNormal3fv (m_pNormal[x + (y + 0) * m_unSize]);
					glVertex3i (x, y + 0, (int)(m_pucHeightmap[x + (y + 0) * m_unSize] / HEIGHT_DIV));
				}
			glEnd ();
		}
	
	glPopMatrix ();

	glDisable (GL_CULL_FACE);
	glDisable (GL_TEXTURE_2D);
}

void CTerrain::_NormalCalculation ()
{
	gtl::CVector3<float> DotCenter;
	gtl::CVector3<float> DotFrist;
	gtl::CVector3<float> DotSecond;

	gtl::CVector3<float>* pNormalPerFaceBuffer1 = new gtl::CVector3<float>[m_unSize*m_unSize];
	gtl::CVector3<float>* pNormalPerFaceBuffer2 = new gtl::CVector3<float>[m_unSize*m_unSize];

	m_pNormal = new gtl::CVector3<float>[m_unSize*m_unSize];

	int x, y;

	// Groove - 14/07/2003 - Frist find normal per face
	for (y=0; y<(m_unSize-1); y++)
	{
		for (x=0; x<(m_unSize-1); x++)
		{
			DotCenter = gtl::CVector3<float> ((float)(x + 0), (float)(y + 0), m_pucHeightmap[(x+0)+(y+0)*m_unSize]/HEIGHT_DIV);
			DotFrist  = gtl::CVector3<float> ((float)(x + 1), (float)(y + 0), m_pucHeightmap[(x+1)+(y+0)*m_unSize]/HEIGHT_DIV);
			DotSecond = gtl::CVector3<float> ((float)(x + 0), (float)(y + 1), m_pucHeightmap[(x+0)+(y+1)*m_unSize]/HEIGHT_DIV);
			pNormalPerFaceBuffer1[y*m_unSize+x] = (DotFrist-DotCenter)^(DotSecond-DotCenter);
		}
	}

	// Groove - 14/07/2003 - Second find normal per vertex
	for (y=0; y<(m_unSize-1); y++)
	{
		for (x=0; x<(m_unSize-1); x++)
		{
			DotCenter = gtl::CVector3<float> ((float)(x + 1), (float)(y + 1), m_pucHeightmap[(x+1)+(y+1)*m_unSize]/HEIGHT_DIV);
			DotFrist  = gtl::CVector3<float> ((float)(x + 0), (float)(y + 1), m_pucHeightmap[(x+0)+(y+1)*m_unSize]/HEIGHT_DIV);
			DotSecond = gtl::CVector3<float> ((float)(x + 1), (float)(y + 0), m_pucHeightmap[(x+1)+(y+0)*m_unSize]/HEIGHT_DIV);
			pNormalPerFaceBuffer2[y*m_unSize+x] = (DotFrist-DotCenter)^(DotSecond-DotCenter);
		}
	}

	for (y=1; y<(m_unSize-1); y++)
	{
		for (x=1; x<(m_unSize-1); x++)
		{
			m_pNormal[x+y*m_unSize] = ((
				pNormalPerFaceBuffer1[(x+0)+(y+0)*m_unSize] +
				pNormalPerFaceBuffer1[(x+1)+(y+0)*m_unSize] +
				pNormalPerFaceBuffer1[(x+1)+(y+1)*m_unSize] +
				pNormalPerFaceBuffer2[(x+0)+(y+0)*m_unSize]	+
				pNormalPerFaceBuffer2[(x+0)+(y+1)*m_unSize]	+ 
				pNormalPerFaceBuffer2[(x+1)+(y+1)*m_unSize]) / 6).GetNormalize ();
		}
	}

	// Groove - 14/07/2003 - Init border with a value
	for (y=0; y<m_unSize; y++)
	{
		m_pNormal[0+y*m_unSize] = gtl::CVector3<float> (0,0,0);
	}

	for (y=0; y<m_unSize; y++)
	{
		m_pNormal[(m_unSize-2)+y*m_unSize] = gtl::CVector3<float> (0,0,0);
	}

	for (x=0; x<m_unSize; x++)
	{
		m_pNormal[x+y*0] = gtl::CVector3<float> (0,0,0);
	}

	for (x=0; x<m_unSize; x++)
	{
		m_pNormal[x+y*(m_unSize-1)] = gtl::CVector3<float> (0,0,0);
	}

	delete pNormalPerFaceBuffer1;
	delete pNormalPerFaceBuffer2;
}

gtl::CVector3<float> CTerrain::Normal (gtl::CVector3<float> Position)
{
	int x = static_cast<int>(Position (gtl::X));
	if (x < 0)
		x = 0;
	if (x > (m_unSize - 1))
		x = m_unSize - 1;

	int y = static_cast<int>(Position (gtl::Y));
	if (y < 0)
		y = 0;
	if (y > (m_unSize - 1))
		y = m_unSize - 1;

	return m_pNormal[x + y * m_unSize];
}

float CTerrain::Height (gtl::CVector3<float> Position)
{
	int x = static_cast<int>(Position (gtl::X));
	if (x < 0)
		x = 0;
	if (x > (m_unSize - 1))
		x = m_unSize - 1;

	int y = static_cast<int>(Position (gtl::Y));
	if (y < 0)
		y = 0;
	if (y > (m_unSize - 1))
		y = m_unSize - 1;

	return m_pucHeightmap[x + y * m_unSize] / HEIGHT_DIV;
	//return m_pNormalFace[Coord (gtl::X) + Coord (gtl::Y) * m_unSize];
//	return 0;//m_pucHeightmap[Coord (gtl::X) + Coord (gtl::Y) * m_unSize] / HEIGHT_DIV;
}

