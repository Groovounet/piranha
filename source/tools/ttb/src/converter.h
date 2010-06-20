#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <gtl_image_tga.h>
#include <string>
#include <list>

typedef struct 
{
	unsigned char m_ucHeightNoneMin;
	unsigned char m_ucHeightFullMin;
	unsigned char m_ucHeightFullMax;
	unsigned char m_ucHeightNoneMax;
	std::string m_szFilename;
} SLevel;

typedef struct 
{
	std::string m_szHeightmap;
	std::string m_szFilename;
	std::list<SLevel> m_Level;
} STexture;

class CConverter
{
private:
	std::list<STexture> m_Data;
	unsigned char m_ucTextureNbr;
	gtl::CImageTGA *m_pTextureBuffer;
	unsigned char *m_pucTextureData;
	unsigned short m_unTextureSizeX;
	unsigned short m_unTextureSizeY;

	unsigned char *m_pucHeightMapData;
	unsigned short m_unHeightMapSizeX;
	unsigned short m_unHeightMapSizeY;
	
	void Init ();

public:
	CConverter ();
	~CConverter ();

	bool BuildTexture (const STexture & Texture);
	bool BuildTextureRGB ();
	bool LoadGenTex (const STexture & Texture);
	float FindBlend (const SLevel & Level, unsigned char iHeight);
	bool CheckTexGenSize ();
	bool LoadHeightmap (const char* szFileName);
	bool SaveTexture (const char* szFileName);

	void Add (const STexture & Texture);
	bool Run ();
};

#endif //__CONVERTER_H__