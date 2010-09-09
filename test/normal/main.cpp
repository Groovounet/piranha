#include "../../lib/gtl/include/gtl.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static const char* HEIGHTMAP = "./heightmap.tga";
unsigned char* g_pucHeightmap;
gtl::CVector3<float>* g_pNormal;
gtl::CVector3<float> g_Scale (1.0f, 1.0f, 1.0f);
int g_iSize;

void _FastNormalCalculationAddress ();
void _FastNormalCalculationArray ();
void _BruteNormalCalculationAddress ();
void _BruteNormalCalculationArray ();

int main ()
{
    gtl::CImageTGA HeightMap (HEIGHTMAP);
	g_iSize = HeightMap.Width ();

    g_pucHeightmap = new unsigned char [g_iSize * g_iSize];

    for (int j = 0; j < g_iSize; j++)
        for (int i = 0; i < g_iSize; i++)
            *(g_pucHeightmap + (g_iSize * j + i)) = *(HeightMap.Data () + (g_iSize * 3 * j + (i * 3)));

    clock_t Time1 = clock ();
    //for (int i = 0; i < 100; i++)
        _FastNormalCalculationAddress ();
    printf ("_FastNormalCalculationAddress : %d\n", clock () - Time1);

    clock_t Time2 = clock ();
    //for (int i = 0; i < 100; i++)
        _FastNormalCalculationArray ();
    printf ("_FastNormalCalculationArray : %d\n", clock () - Time2);

    clock_t Time3 = clock ();
    //for (int i = 0; i < 100; i++)
        _BruteNormalCalculationAddress ();
    printf ("_BruteNormalCalculationAddress : %d\n", clock () - Time3);

    clock_t Time4 = clock ();
    //for (int i = 0; i < 100; i++)
        _BruteNormalCalculationArray ();
    printf ("_BruteNormalCalculationArray : %d\n", clock () - Time4);

    system ("pause");
}

void _FastNormalCalculationAddress ()
{
	if (!g_pNormal)
    {
		g_pNormal = new gtl::CVector3<float> [(g_iSize + 1) * (g_iSize + 1)];
	    for (int y = 0; y < g_iSize; y++)
		    *(g_pNormal + (0 + y * g_iSize)) = gtl::CVector3<float> (0, 0, 0);

	    for (int y = 0; y < g_iSize; y++)
		    *(g_pNormal + (g_iSize - 1) + y * g_iSize) = gtl::CVector3<float> (0, 0, 0);

	    for (int x = 0; x < g_iSize; x++)
		    *(g_pNormal + (x + y * 0)) = gtl::CVector3<float> (0, 0, 0);

	    for (int x = 0; x < g_iSize; x++)
		    *(g_pNormal + (x + y * (g_iSize - 1))) = gtl::CVector3<float> (0, 0, 0);
    }

	for (int y = 1; y < (g_iSize - 1); y++)
	{
		for (int x = 1; x < (g_iSize - 1); x++)
		{
            float fH1 = *(g_pucHeightmap + ((x + 1) + (y + 0) * g_iSize)) * g_Scale (gtl::Z);
            float fH2 = *(g_pucHeightmap + ((x + 0) + (y + 1) * g_iSize)) * g_Scale (gtl::Z);
            float fH3 = *(g_pucHeightmap + ((x - 1) + (y + 0) * g_iSize)) * g_Scale (gtl::Z);
            float fH4 = *(g_pucHeightmap + ((x + 0) + (y - 1) * g_iSize)) * g_Scale (gtl::Z);
			*(g_pNormal + (x + y * g_iSize)) = gtl::CVector3<float> (fH3 - fH1, fH4 - fH2, 2).Normalize ();
        }
	}

    delete g_pNormal;
    g_pNormal = 0;
}

void _FastNormalCalculationArray ()
{
	if (!g_pNormal)
    {
		g_pNormal = new gtl::CVector3<float> [(g_iSize + 1) * (g_iSize + 1)];
	    for (int y = 0; y < g_iSize; y++)
            g_pNormal[0 + y * g_iSize] = gtl::CVector3<float> (0, 0, 0);

	    for (int y = 0; y < g_iSize; y++)
		    g_pNormal[(g_iSize - 1) + y * g_iSize] = gtl::CVector3<float> (0, 0, 0);

	    for (int x = 0; x < g_iSize; x++)
		    g_pNormal[x + y * 0] = gtl::CVector3<float> (0, 0, 0);

	    for (int x = 0; x < g_iSize; x++)
		    g_pNormal[x + y * (g_iSize - 1)] = gtl::CVector3<float> (0, 0, 0);
    }

	for (int y = 1; y < (g_iSize - 1); y++)
	{
		for (int x = 1; x < (g_iSize - 1); x++)
		{
            float fH1 = g_pucHeightmap[(x + 1) + (y + 0) * g_iSize] * g_Scale (gtl::Z);
            float fH2 = g_pucHeightmap[(x + 0) + (y + 1) * g_iSize] * g_Scale (gtl::Z);
            float fH3 = g_pucHeightmap[(x - 1) + (y + 0) * g_iSize] * g_Scale (gtl::Z);
            float fH4 = g_pucHeightmap[(x + 0) + (y - 1) * g_iSize] * g_Scale (gtl::Z);
			g_pNormal[x + y * g_iSize] = gtl::CVector3<float> (fH3 - fH1, fH4 - fH2, 2).Normalize ();
        }
	}

    delete g_pNormal;
    g_pNormal = 0;
}

void _BruteNormalCalculationAddress ()
{
	gtl::CVector3<float> DotCenter;
	gtl::CVector3<float> DotFrist;
	gtl::CVector3<float> DotSecond;

	gtl::CVector3<float>* pNormalPerFaceBuffer1 = new gtl::CVector3<float>[(g_iSize)*(g_iSize)];
	gtl::CVector3<float>* pNormalPerFaceBuffer2 = new gtl::CVector3<float>[(g_iSize)*(g_iSize)];

	int x, y;

    if (!g_pNormal)
    {
		g_pNormal = new gtl::CVector3<float> [(g_iSize+1)*(g_iSize+1)];
	    for (y=0; y<g_iSize; y++)
		    *(g_pNormal + (0 + y * g_iSize)) = gtl::CVector3<float> (0,0,0);

	    for (y=0; y<g_iSize; y++)
		    *(g_pNormal + ((g_iSize-1)+y*g_iSize)) = gtl::CVector3<float> (0,0,0);

	    for (x=0; x<g_iSize; x++)
		    *(g_pNormal + (x+y*0)) = gtl::CVector3<float> (0,0,0);

	    for (x=0; x<g_iSize; x++)
		    *(g_pNormal + (x+y*(g_iSize-1))) = gtl::CVector3<float> (0,0,0);
    }

	for (y = 0; y < (g_iSize - 1); y++)
	{
		for (x = 0; x < (g_iSize - 1); x++)
		{
            DotCenter = gtl::CVector3<float> ((x + 0) * g_Scale (gtl::X), (y + 0) * g_Scale (gtl::Y), *(g_pucHeightmap + ((x + 0) + (y + 0) * g_iSize)) * g_Scale (gtl::Z));
			DotFrist  = gtl::CVector3<float> ((x + 1) * g_Scale (gtl::X), (y + 0) * g_Scale (gtl::Y), *(g_pucHeightmap + ((x + 1) + (y + 0) * g_iSize)) * g_Scale (gtl::Z));
			DotSecond = gtl::CVector3<float> ((x + 0) * g_Scale (gtl::X), (y + 1) * g_Scale (gtl::Y), *(g_pucHeightmap + ((x + 0) + (y + 1) * g_iSize)) * g_Scale (gtl::Z));
			*(pNormalPerFaceBuffer1 + (y * g_iSize + x)) = (DotFrist - DotCenter) ^ (DotSecond - DotCenter);
		}
	}

	for (y = 0; y < (g_iSize - 1); y++)
	{
		for (x = 0; x < (g_iSize - 1); x++)
		{
			DotCenter = gtl::CVector3<float> ((x + 1) * g_Scale (gtl::X), (y + 1) * g_Scale (gtl::Y), *(g_pucHeightmap + ((x + 1) + (y + 1) * g_iSize)) * g_Scale (gtl::Z));
			DotFrist  = gtl::CVector3<float> ((x + 0) * g_Scale (gtl::X), (y + 1) * g_Scale (gtl::Y), *(g_pucHeightmap + ((x + 0) + (y + 1) * g_iSize)) * g_Scale (gtl::Z));
			DotSecond = gtl::CVector3<float> ((x + 1) * g_Scale (gtl::X), (y + 0) * g_Scale (gtl::Y), *(g_pucHeightmap + ((x + 1) + (y + 0) * g_iSize)) * g_Scale (gtl::Z));
			*(pNormalPerFaceBuffer2 + (y * g_iSize + x)) = (DotFrist-DotCenter)^(DotSecond-DotCenter);
		}
	}

	for (y = 1; y < (g_iSize - 1); y++)
	{
		for (x = 1; x < (g_iSize - 1); x++)
		{
			*(g_pNormal + (x + y * g_iSize)) = (
                *(pNormalPerFaceBuffer1 + ((x+0)+(y+0)*g_iSize)) + 
				*(pNormalPerFaceBuffer1 + ((x+1)+(y+0)*g_iSize)) +
				*(pNormalPerFaceBuffer1 + ((x+1)+(y+1)*g_iSize)) +
				*(pNormalPerFaceBuffer2 + ((x+0)+(y+0)*g_iSize)) +
				*(pNormalPerFaceBuffer2 + ((x+0)+(y+1)*g_iSize)) +
				*(pNormalPerFaceBuffer2 + ((x+1)+(y+1)*g_iSize))) / 6;
		}
	}

	delete pNormalPerFaceBuffer1;
	delete pNormalPerFaceBuffer2;

    delete g_pNormal;
    g_pNormal = 0;
}

void _BruteNormalCalculationArray ()
{
	gtl::CVector3<float> DotCenter;
	gtl::CVector3<float> DotFrist;
	gtl::CVector3<float> DotSecond;

	gtl::CVector3<float>* pNormalPerFaceBuffer1 = new gtl::CVector3<float>[(g_iSize)*(g_iSize)];
	gtl::CVector3<float>* pNormalPerFaceBuffer2 = new gtl::CVector3<float>[(g_iSize)*(g_iSize)];

	int x, y;

    if (!g_pNormal)
    {
		g_pNormal = new gtl::CVector3<float> [(g_iSize+1)*(g_iSize+1)];
	    for (y=0; y<g_iSize; y++)
		    *(g_pNormal + (0 + y * g_iSize)) = gtl::CVector3<float> (0,0,0);

	    for (y=0; y<g_iSize; y++)
		    *(g_pNormal + ((g_iSize-1)+y*g_iSize)) = gtl::CVector3<float> (0,0,0);

	    for (x=0; x<g_iSize; x++)
		    *(g_pNormal + (x+y*0)) = gtl::CVector3<float> (0,0,0);

	    for (x=0; x<g_iSize; x++)
		    *(g_pNormal + (x+y*(g_iSize-1))) = gtl::CVector3<float> (0,0,0);
    }

	for (y = 0; y < (g_iSize - 1); y++)
	{
		for (x = 0; x < (g_iSize - 1); x++)
		{
            DotCenter = gtl::CVector3<float> ((x + 0) * g_Scale (gtl::X), (y + 0) * g_Scale (gtl::Y), g_pucHeightmap[(x + 0) + (y + 0) * g_iSize] * g_Scale (gtl::Z));
			DotFrist  = gtl::CVector3<float> ((x + 1) * g_Scale (gtl::X), (y + 0) * g_Scale (gtl::Y), g_pucHeightmap[(x + 1) + (y + 0) * g_iSize] * g_Scale (gtl::Z));
			DotSecond = gtl::CVector3<float> ((x + 0) * g_Scale (gtl::X), (y + 1) * g_Scale (gtl::Y), g_pucHeightmap[(x + 0) + (y + 1) * g_iSize] * g_Scale (gtl::Z));
			pNormalPerFaceBuffer1[y * g_iSize + x] = (DotFrist - DotCenter) ^ (DotSecond - DotCenter);
		}
	}

	for (y = 0; y < (g_iSize - 1); y++)
	{
		for (x = 0; x < (g_iSize - 1); x++)
		{
			DotCenter = gtl::CVector3<float> ((x + 1) * g_Scale (gtl::X), (y + 1) * g_Scale (gtl::Y), g_pucHeightmap[(x + 1) + (y + 1) * g_iSize] * g_Scale (gtl::Z));
			DotFrist  = gtl::CVector3<float> ((x + 0) * g_Scale (gtl::X), (y + 1) * g_Scale (gtl::Y), g_pucHeightmap[(x + 0) + (y + 1) * g_iSize] * g_Scale (gtl::Z));
			DotSecond = gtl::CVector3<float> ((x + 1) * g_Scale (gtl::X), (y + 0) * g_Scale (gtl::Y), g_pucHeightmap[(x + 1) + (y + 0) * g_iSize] * g_Scale (gtl::Z));
			pNormalPerFaceBuffer2[y*g_iSize+x] = (DotFrist-DotCenter)^(DotSecond-DotCenter);
		}
	}

	for (y = 1; y < (g_iSize - 1); y++)
	{
		for (x = 1; x < (g_iSize - 1); x++)
		{
			g_pNormal[x+y*g_iSize] = (pNormalPerFaceBuffer1[(x+0)+(y+0)*g_iSize]
				+ pNormalPerFaceBuffer1[(x+1)+(y+0)*g_iSize]
				+ pNormalPerFaceBuffer1[(x+1)+(y+1)*g_iSize]
				+ pNormalPerFaceBuffer2[(x+0)+(y+0)*g_iSize]
				+ pNormalPerFaceBuffer2[(x+0)+(y+1)*g_iSize]
				+ pNormalPerFaceBuffer2[(x+1)+(y+1)*g_iSize]) / 6;
		}
	}

	delete pNormalPerFaceBuffer1;
	delete pNormalPerFaceBuffer2;

    delete g_pNormal;
    g_pNormal = 0;
}
