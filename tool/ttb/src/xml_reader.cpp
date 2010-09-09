/***********************************************\
	T.A.M.
*************************************************
	G-Truc Creation, www.g-truc.net
*************************************************
	xml_reader.cpp, 11/10/2003
\***********************************************/

#include "xml_reader.h"

void CXMLReader::Init ()
{
	m_Texture.m_Level.clear ();
	m_Texture.m_szFilename.clear ();
	m_Texture.m_szHeightmap.clear ();
}

void CXMLReader::startElement (const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attributes)
{
	char* szLocalName = XMLString::transcode (localname);

	if (!strcmp (szLocalName, "texture"))
	{
		int iLenght = attributes.getLength ();
		for (int i = 0; i < iLenght; i++)
		{
			char* szAttName = XMLString::transcode (attributes.getLocalName (i));
			if (!strcmp (szAttName, "filename"))
			{
				char* szValue = XMLString::transcode (attributes.getValue (i));
				m_Texture.m_szFilename = szValue;
				XMLString::release (&szValue);
			}
			if (!strcmp (szAttName, "heightmap"))
			{
				char* szValue = XMLString::transcode (attributes.getValue (i));
				m_Texture.m_szHeightmap = szValue;
				XMLString::release (&szValue);
			}
			XMLString::release (&szAttName);
		}
	}

	if (!strcmp (szLocalName, "level"))
	{
		SLevel Level;

		int iLenght = attributes.getLength ();
		for (int i = 0; i < iLenght; i++)
		{
			char* szAttName = XMLString::transcode (attributes.getLocalName (i));

			if (!strcmp (szAttName, "filename"))
			{
				char* szValue = XMLString::transcode (attributes.getValue (i));
				Level.m_szFilename = szValue;
				XMLString::release (&szValue);
			}

			if (!strcmp (szAttName, "heightnonemin"))
			{
				char* szValue = XMLString::transcode (attributes.getValue (i));
				Level.m_ucHeightNoneMin = atoi(szValue);
				XMLString::release (&szValue);
			}

			if (!strcmp (szAttName, "heightfullmin"))
			{
				char* szValue = XMLString::transcode (attributes.getValue (i));
				Level.m_ucHeightFullMin = atoi(szValue);
				XMLString::release (&szValue);
			}

			if (!strcmp (szAttName, "heightfullmax"))
			{
				char* szValue = XMLString::transcode (attributes.getValue (i));
				Level.m_ucHeightFullMax = atoi(szValue);
				XMLString::release (&szValue);
			}

			if (!strcmp (szAttName, "heightnonemax"))
			{
				char* szValue = XMLString::transcode (attributes.getValue (i));
				Level.m_ucHeightNoneMax = atoi(szValue);
				XMLString::release (&szValue);
			}

			XMLString::release (&szAttName);
		}
		m_Texture.m_Level.push_back (Level);
	}

	XMLString::release (&szLocalName);
}

void CXMLReader::endElement (const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	char* szLocalName = XMLString::transcode (localname);
	if (!strcmp (szLocalName, "texture"))
	{
		m_Converter.Add (m_Texture);
		Init ();
	}
	XMLString::release (&szLocalName);

}