#include "xml_reader.h"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <stdio.h>

void info ()
{
	printf ("*************************************************\n");
	printf ("\tttb : 19/12/2003\n");
	printf ("\tpar Groove, groove@g-truc.net\n");
	printf ("*************************************************\n");
}

int main (int argc, char* argv[])
{
	info ();

	if (argc != 2)
		return 1;

	try
    {
         XMLPlatformUtils::Initialize ();
    }

	catch (const XMLException& toCatch)
    {
		char* szMsg = XMLString::transcode (toCatch.getMessage ());
		printf ("Error during initialization! : %s\n", szMsg);
		return 1;
    }
	
	SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader ();
	CXMLReader Handler;
	
	pParser->setContentHandler (&Handler);
	pParser->setErrorHandler (&Handler);
	pParser->parse (argv[1]);
    delete pParser;
	
	XMLPlatformUtils::Terminate ();

	Handler.Run ();

	return 0;
}