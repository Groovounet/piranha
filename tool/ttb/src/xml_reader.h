#ifndef __XML_READER_H__
#define __XML_READER_H__

#include "converter.h"
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <stddef.h>

XERCES_CPP_NAMESPACE_USE

class CXMLReader : public DefaultHandler
{
public:
	bool Run () {return m_Converter.Run ();}

private :
	STexture m_Texture;
	CConverter m_Converter;

	void Init ();
	
	virtual void startElement (const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attributes);
	virtual void endElement (const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
};

#endif //__XML_READER_H__