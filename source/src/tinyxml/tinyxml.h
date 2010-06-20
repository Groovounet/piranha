/*
www.sourceforge.net/projects/tinyxml
Original code (2.0 and earlier )copyright (c) 2000-2002 Lee Thomason (www.grinninglizard.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/


#ifndef TINYXML_INCLUDED
#define TINYXML_INCLUDED

#ifdef _MSC_VER
#pragma warning( disable : 4530 )
#pragma warning( disable : 4786 )
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>
#include <iostream>
#define TIXML_STRING	std::string
#define TIXML_ISTREAM	std::istream
#define TIXML_OSTREAM	std::ostream

namespace tixml {

// Help out windows:
#if defined( _DEBUG ) && !defined( DEBUG )
#define DEBUG
#endif

#if defined( DEBUG ) && defined( _MSC_VER )
#include <windows.h>
#define TIXML_LOG OutputDebugString
#else
#define TIXML_LOG printf
#endif
/*
#ifdef TIXML_USE_STL
	#include <string>
 	#include <iostream>
	#define TIXML_STRING	std::string
	#define TIXML_ISTREAM	std::istream
	#define TIXML_OSTREAM	std::ostream
#else
	#include "tinystr.h"
	#define TIXML_STRING	TiXmlString
	#define TIXML_OSTREAM	TiXmlOutStream
#endif
*/

class Document;
class Element;
class Comment;
class CUnknown;
class CAttribute;
class Text;
class Declaration;
class ParsingData;

const int TIXML_MAJOR_VERSION = 2;
const int TIXML_MINOR_VERSION = 3;
const int TIXML_PATCH_VERSION = 2;

/*	Internal structure for tracking location of items 
	in the XML file.
*/
struct Cursor
{
	Cursor()		{ Clear(); }
	void Clear()		{ row = col = -1; }

	int row;	// 0 based.
	int col;	// 0 based.
};


// Only used by CAttribute::Query functions
enum 
{ 
	TIXML_SUCCESS,
	TIXML_NO_ATTRIBUTE,
	TIXML_WRONG_TYPE
};


// Used by the parsing routines.
enum Encoding
{
	ENCODING_UNKNOWN,
	ENCODING_UTF8,
	ENCODING_LEGACY
};

const Encoding DEFAULT_ENCODING = ENCODING_UNKNOWN;

/** Base is a base class for every class in TinyXml.
	It does little except to establish that TinyXml classes
	can be printed and provide some utility functions.

	In XML, the document and elements can contain
	other elements and other types of nodes.

	@verbatim
	A Document can contain:	Element	(container or leaf)
							Comment (leaf)
							CUnknown (leaf)
							Declaration( leaf )

	An Element can contain:	Element (container or leaf)
							Text	(leaf)
							Attributes (not on tree)
							Comment (leaf)
							CUnknown (leaf)

	A Decleration contains: Attributes (not on tree)
	@endverbatim
*/
class Base
{
	friend class CNode;
	friend class Element;
	friend class Document;

public:
	Base()	:	userData(0) {}
	virtual ~Base()					{}

	/**	All TinyXml classes can print themselves to a filestream.
		This is a formatted print, and will insert tabs and newlines.
		
		(For an unformatted stream, use the << operator.)
	*/
	virtual void Print( FILE* cfile, int depth ) const = 0;

	/**	The world does not agree on whether white space should be kept or
		not. In order to make everyone happy, these global, static functions
		are provided to set whether or not TinyXml will condense all white space
		into a single space or not. The default is to condense. Note changing this
		values is not thread safe.
	*/
	static void SetCondenseWhiteSpace( bool condense )		{ condenseWhiteSpace = condense; }

	/// Return the current white space setting.
	static bool IsWhiteSpaceCondensed()						{ return condenseWhiteSpace; }

	/** Return the position, in the original source file, of this node or attribute.
		The row and column are 1-based. (That is the first row and first column is
		1,1). If the returns values are 0 or less, then the parser does not have
		a row and column value.

		Generally, the row and column value will be set when the Document::Load(),
		Document::LoadFile(), or any CNode::Parse() is called. It will NOT be set
		when the DOM was created from operator>>.

		The values reflect the initial load. Once the DOM is modified programmatically
		(by adding or changing nodes and attributes) the new values will NOT update to
		reflect changes in the document.

		There is a minor performance cost to computing the row and column. Computation
		can be disabled if Document::SetTabSize() is called with 0 as the value.

		@sa Document::SetTabSize()
	*/
	int Row() const			{ return location.row + 1; }
	int Column() const		{ return location.col + 1; }	///< See Row()

	void  SetUserData( void* user )			{ userData = user; }
	void* GetUserData()						{ return userData; }

	// Table that returs, for a given lead byte, the total number of bytes
	// in the UTF-8 sequence.
	static const int utf8ByteTable[256];

	virtual const char* Parse(	const char* p, 
								ParsingData* data, 
								Encoding encoding /*= ENCODING_UNKNOWN */ ) = 0;

protected:

	// See STL_STRING_BUG
	// Utility class to overcome a bug.
	class StringToBuffer
	{
	  public:
		StringToBuffer( const TIXML_STRING& str );
		~StringToBuffer();
		char* buffer;
	};

	static const char*	SkipWhiteSpace( const char*, Encoding encoding );
	inline static bool	IsWhiteSpace( char c )		
	{ 
		return ( isspace( (unsigned char) c ) || c == '\n' || c == '\r' ); 
	}

	virtual void StreamOut (TIXML_OSTREAM *) const = 0;
/*
	#ifdef TIXML_USE_STL
	    static bool	StreamWhiteSpace( TIXML_ISTREAM * in, TIXML_STRING * tag );
	    static bool StreamTo( TIXML_ISTREAM * in, int character, TIXML_STRING * tag );
	#endif
*/
	static bool	StreamWhiteSpace( TIXML_ISTREAM * in, TIXML_STRING * tag );
	static bool StreamTo( TIXML_ISTREAM * in, int character, TIXML_STRING * tag );
    
    /*	Reads an XML name into the string provided. Returns
		a pointer just past the last character of the name,
		or 0 if the function has an error.
	*/
	static const char* ReadName( const char* p, TIXML_STRING* name, Encoding encoding );

	/*	Reads text. Returns a pointer past the given end tag.
		Wickedly complex options, but it keeps the (sensitive) code in one place.
	*/
	static const char* ReadText(	const char* in,				// where to start
									TIXML_STRING* text,			// the string read
									bool ignoreWhiteSpace,		// whether to keep the white space
									const char* endTag,			// what ends this text
									bool ignoreCase,			// whether to ignore case in the end tag
									Encoding encoding );	// the current encoding

	// If an entity has been found, transform it into a character.
	static const char* GetEntity( const char* in, char* value, int* length, Encoding encoding );

	// Get a character, while interpreting entities.
	// The length can be from 0 to 4 bytes.
	inline static const char* GetChar( const char* p, char* _value, int* length, Encoding encoding )
	{
		assert( p );
		if ( encoding == ENCODING_UTF8 )
		{
			*length = utf8ByteTable[ *((unsigned char*)p) ];
			assert( *length >= 0 && *length < 5 );
		}
		else
		{
			*length = 1;
		}

		if ( *length == 1 )
		{
			if ( *p == '&' )
				return GetEntity( p, _value, length, encoding );
			*_value = *p;
			return p+1;
		}
		else if ( *length )
		{
			strncpy( _value, p, *length );
			return p + (*length);
		}
		else
		{
			// Not valid text.
			return 0;
		}
	}

	// Puts a string to a stream, expanding entities as it goes.
	// Note this should not contian the '<', '>', etc, or they will be transformed into entities!
	static void PutString( const TIXML_STRING& str, TIXML_OSTREAM* out );

	static void PutString( const TIXML_STRING& str, TIXML_STRING* out );

	// Return true if the next characters in the stream are any of the endTag sequences.
	// Ignore case only works for english, and should only be relied on when comparing
	// to Engilish words: StringEqual( p, "version", true ) is fine.
	static bool StringEqual(	const char* p,
								const char* endTag,
								bool ignoreCase,
								Encoding encoding );


	enum
	{
		TIXML_NO_ERROR = 0,
		TIXML_ERROR,
		TIXML_ERROR_OPENING_FILE,
		TIXML_ERROR_OUT_OF_MEMORY,
		TIXML_ERROR_PARSING_ELEMENT,
		TIXML_ERROR_FAILED_TO_READ_ELEMENT_NAME,
		TIXML_ERROR_READING_ELEMENT_VALUE,
		TIXML_ERROR_READING_ATTRIBUTES,
		TIXML_ERROR_PARSING_EMPTY,
		TIXML_ERROR_READING_END_TAG,
		TIXML_ERROR_PARSING_UNKNOWN,
		TIXML_ERROR_PARSING_COMMENT,
		TIXML_ERROR_PARSING_DECLARATION,
		TIXML_ERROR_DOCUMENT_EMPTY,
		TIXML_ERROR_EMBEDDED_NULL,

		TIXML_ERROR_STRING_COUNT
	};
	static const char* errorString[ TIXML_ERROR_STRING_COUNT ];

	Cursor location;

    /// Field containing a generic user pointer
	void*			userData;
	
	// None of these methods are reliable for any language except English.
	// Good for approximation, not great for accuracy.
	static int IsAlpha( unsigned char anyByte, Encoding encoding );
	static int IsAlphaNum( unsigned char anyByte, Encoding encoding );
	inline static int ToLower( int v, Encoding encoding )
	{
		if ( encoding == ENCODING_UTF8 )
		{
			if ( v < 128 ) return tolower( v );
			return v;
		}
		else
		{
			return tolower( v );
		}
	}
	static void ConvertUTF32ToUTF8( unsigned long input, char* output, int* length );

private:
	Base( const Base& );				// not implemented.
	void operator=( const Base& base );	// not allowed.

	struct Entity
	{
		const char*     str;
		unsigned int	strLength;
		char		    chr;
	};
	enum
	{
		NUM_ENTITY = 5,
		MAX_ENTITY_LENGTH = 6

	};
	static Entity entity[ NUM_ENTITY ];
	static bool condenseWhiteSpace;
};


/** The parent class for everything in the Document Object Model.
	(Except for attributes).
	Nodes have siblings, a parent, and children. A node can be
	in a document, or stand on its own. The type of a Node
	can be queried, and it can be cast to its more defined type.
*/
class CNode : public Base
{
	friend class Document;
	friend class Element;

public:
//	#ifdef TIXML_USE_STL	

	    /** An input stream operator, for every class. Tolerant of newlines and
		    formatting, but doesn't expect them.
	    */
	    friend std::istream& operator >> (std::istream& in, CNode& base);

	    /** An output stream operator, for every class. Note that this outputs
		    without any newlines or formatting, as opposed to Print(), which
		    includes tabs and new lines.

		    The operator<< and operator>> are not completely symmetric. Writing
		    a node to a stream is very well defined. You'll get a nice stream
		    of output, without any extra whitespace or newlines.
		    
		    But reading is not as well defined. (As it always is.) If you create
		    a Element (for example) and read that from an input stream,
		    the text needs to define an element or junk will result. This is
		    true of all input streams, but it's worth keeping in mind.

		    A Document will read nodes until it reads a root element, and
			all the children of that root element.
	    */	
	    friend std::ostream& operator<< (std::ostream& out, const CNode& base);

		/// Appends the XML node or attribute to a std::string.
		friend std::string& operator<< (std::string& out, const CNode& base );
/*
	#else
	    // Used internally, not part of the public API.
	    friend TIXML_OSTREAM& operator<< (TIXML_OSTREAM& out, const CNode& base);
	#endif
*/
	/** The types of XML nodes supported by TinyXml. (All the
			unsupported types are picked up by UNKNOWN.)
	*/
	enum NodeType
	{
		DOCUMENT,
		ELEMENT,
		COMMENT,
		UNKNOWN,
		TEXT,
		DECLARATION,
		TYPECOUNT
	};

	virtual ~CNode();

	/** The meaning of 'value' changes for the specific type of
		CNode.
		@verbatim
		Document:	filename of the xml file
		Element:	name of the element
		Comment:	the comment text
		CUnknown:	the tag contents
		Text:		the text string
		@endverbatim

		The subclasses will wrap this function.
	*/
	const char * Value() const { return value.c_str (); }

	/** Changes the value of the node. Defined as:
		@verbatim
		Document:	filename of the xml file
		Element:	name of the element
		Comment:	the comment text
		CUnknown:	the tag contents
		Text:		the text string
		@endverbatim
	*/
	void SetValue(const char * _value) { value = _value;}
/*
    #ifdef TIXML_USE_STL
	/// STL std::string form.
	void SetValue( const std::string& _value )    
	{	  
		StringToBuffer buf( _value );
		SetValue( buf.buffer ? buf.buffer : "" );    	
	}	
	#endif
*/
	/// STL std::string form.
	void SetValue( const std::string& _value )    
	{	  
		StringToBuffer buf( _value );
		SetValue( buf.buffer ? buf.buffer : "" );    	
	}	
    
    /// Delete all the children of this node. Does not affect 'this'.
	void Clear();

	/// One step up the DOM.
	CNode* Parent() const					{ return parent; }

	CNode* FirstChild()	const	{ return firstChild; }		///< The first child of this node. Will be null if there are no children.
	CNode* FirstChild( const char * value ) const;			///< The first child of this node with the matching 'value'. Will be null if none found.

	CNode* LastChild() const	{ return lastChild; }		/// The last child of this node. Will be null if there are no children.
	CNode* LastChild( const char * value ) const;			/// The last child of this node matching 'value'. Will be null if there are no children.
/*
    #ifdef TIXML_USE_STL
	CNode* FirstChild( const std::string& _value ) const	{	return FirstChild (_value.c_str ());	}	///< STL std::string form.
	CNode* LastChild( const std::string& _value ) const		{	return LastChild (_value.c_str ());	}	///< STL std::string form.
	#endif
*/
	CNode* FirstChild( const std::string& _value ) const	{	return FirstChild (_value.c_str ());	}	///< STL std::string form.
	CNode* LastChild( const std::string& _value ) const		{	return LastChild (_value.c_str ());	}	///< STL std::string form.

    /** An alternate way to walk the children of a node.
		One way to iterate over nodes is:
		@verbatim
			for( child = parent->FirstChild(); child; child = child->NextSibling() )
		@endverbatim

		IterateChildren does the same thing with the syntax:
		@verbatim
			child = 0;
			while( child = parent->IterateChildren( child ) )
		@endverbatim

		IterateChildren takes the previous child as input and finds
		the next one. If the previous child is null, it returns the
		first. IterateChildren will return null when done.
	*/
	CNode* IterateChildren( CNode* previous ) const;

	/// This flavor of IterateChildren searches for children with a particular 'value'
	CNode* IterateChildren( const char * value, CNode* previous ) const;
/*
    #ifdef TIXML_USE_STL
	CNode* IterateChildren( const std::string& _value, CNode* previous ) const	{	return IterateChildren (_value.c_str (), previous);	}	///< STL std::string form.
	#endif
*/
	CNode* IterateChildren( const std::string& _value, CNode* previous ) const	{	return IterateChildren (_value.c_str (), previous);	}	///< STL std::string form.

	/** Add a new node related to this. Adds a child past the LastChild.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	CNode* InsertEndChild( const CNode& addThis );


	/** Add a new node related to this. Adds a child past the LastChild.

		NOTE: the node to be added is passed by pointer, and will be
		henceforth owned (and deleted) by tinyXml. This method is efficient
		and avoids an extra copy, but should be used with care as it
		uses a different memory model than the other insert functions.

		@sa InsertEndChild
	*/
	CNode* LinkEndChild( CNode* addThis );

	/** Add a new node related to this. Adds a child before the specified child.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	CNode* InsertBeforeChild( CNode* beforeThis, const CNode& addThis );

	/** Add a new node related to this. Adds a child after the specified child.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	CNode* InsertAfterChild(  CNode* afterThis, const CNode& addThis );

	/** Replace a child of this node.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	CNode* ReplaceChild( CNode* replaceThis, const CNode& withThis );

	/// Delete a child of this node.
	bool RemoveChild( CNode* removeThis );

	/// Navigate to a sibling node.
	CNode* PreviousSibling() const			{ return prev; }

	/// Navigate to a sibling node.
	CNode* PreviousSibling( const char * ) const;
/*
    #ifdef TIXML_USE_STL
	CNode* PreviousSibling( const std::string& _value ) const	{	return PreviousSibling (_value.c_str ());	}	///< STL std::string form.
	CNode* NextSibling( const std::string& _value) const		{	return NextSibling (_value.c_str ());	}	///< STL std::string form.
	#endif
*/
	CNode* PreviousSibling( const std::string& _value ) const	{	return PreviousSibling (_value.c_str ());	}	///< STL std::string form.
	CNode* NextSibling( const std::string& _value) const		{	return NextSibling (_value.c_str ());	}	///< STL std::string form.
    
    /// Navigate to a sibling node.
	CNode* NextSibling() const				{ return next; }

	/// Navigate to a sibling node with the given 'value'.
	CNode* NextSibling( const char * ) const;

	/** Convenience function to get through elements.
		Calls NextSibling and ToElement. Will skip all non-Element
		nodes. Returns 0 if there is not another element.
	*/
	Element* NextSiblingElement() const;

	/** Convenience function to get through elements.
		Calls NextSibling and ToElement. Will skip all non-Element
		nodes. Returns 0 if there is not another element.
	*/
	Element* NextSiblingElement( const char * ) const;
/*
    #ifdef TIXML_USE_STL
	Element* NextSiblingElement( const std::string& _value) const	{	return NextSiblingElement (_value.c_str ());	}	///< STL std::string form.
	#endif
*/
	Element* NextSiblingElement( const std::string& _value) const	{	return NextSiblingElement (_value.c_str ());	}	///< STL std::string form.

	/// Convenience function to get through elements.
	Element* FirstChildElement()	const;

	/// Convenience function to get through elements.
	Element* FirstChildElement( const char * value ) const;
/*
    #ifdef TIXML_USE_STL
	Element* FirstChildElement( const std::string& _value ) const	{	return FirstChildElement (_value.c_str ());	}	///< STL std::string form.
	#endif
*/
	Element* FirstChildElement( const std::string& _value ) const	{	return FirstChildElement (_value.c_str ());	}	///< STL std::string form.

	/** Query the type (as an enumerated value, above) of this node.
		The possible types are: DOCUMENT, ELEMENT, COMMENT,
								UNKNOWN, TEXT, and DECLARATION.
	*/
	virtual int Type() const	{ return type; }

	/** Return a pointer to the Document this node lives in.
		Returns null if not in a document.
	*/
	tixml::Document* GetDocument() const;

	/// Returns true if this node has no children.
	bool NoChildren() const						{ return !firstChild; }

	tixml::Document* ToDocument()	const		{ return ( this && type == DOCUMENT ) ? (tixml::Document*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	tixml::Element*  ToElement() const		{ return ( this && type == ELEMENT  ) ? (tixml::Element*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	tixml::Comment*  ToComment() const		{ return ( this && type == COMMENT  ) ? (tixml::Comment*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
    tixml::CUnknown*  ToUnknown() const		{ return ( this && type == UNKNOWN  ) ? (tixml::CUnknown*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	Text*	   ToText()    const		{ return ( this && type == TEXT     ) ? (tixml::Text*)     this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	Declaration* ToDeclaration() const	{ return ( this && type == DECLARATION ) ? (Declaration*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.

	/** Create an exact duplicate of this node and return it. The memory must be deleted
		by the caller. 
	*/
	virtual CNode* Clone() const = 0;

protected:
	CNode( NodeType _type );

	// Copy to the allocated object. Shared functionality between Clone, Copy constructor,
	// and the assignment operator.
	void CopyTo( CNode* target ) const;
/*
	#ifdef TIXML_USE_STL
	    // The real work of the input operator.
	    virtual void StreamIn( TIXML_ISTREAM* in, TIXML_STRING* tag ) = 0;
	#endif
*/
    // The real work of the input operator.
    virtual void StreamIn( TIXML_ISTREAM* in, TIXML_STRING* tag ) = 0;

	// Figure out what is at *p, and parse it. Returns null if it is not an xml node.
	CNode* Identify( const char* start, Encoding encoding );

	// Internal Value function returning a TIXML_STRING
	const TIXML_STRING& SValue() const	{ return value ; }

	CNode*		parent;
	NodeType		type;

	CNode*		firstChild;
	CNode*		lastChild;

	TIXML_STRING	value;

	CNode*		prev;
	CNode*		next;

private:
	CNode( const CNode& );				// not implemented.
	void operator=( const CNode& base );	// not allowed.
};


/** An attribute is a name-value pair. Elements have an arbitrary
	number of attributes, each with a unique name.

	@note The attributes are not TiXmlNodes, since they are not
		  part of the tinyXML document object model. There are other
		  suggested ways to look at this problem.
*/
class CAttribute : public Base
{
	friend class TiXmlAttributeSet;

public:
	/// Construct an empty attribute.
	CAttribute() : Base()
	{
		document = 0;
		prev = next = 0;
	}
/*
	#ifdef TIXML_USE_STL
	/// std::string constructor.
	CAttribute( const std::string& _name, const std::string& _value )
	{
		name = _name;
		value = _value;
		document = 0;
		prev = next = 0;
	}
	#endif
*/
	/// std::string constructor.
	CAttribute( const std::string& _name, const std::string& _value )
	{
		name = _name;
		value = _value;
		document = 0;
		prev = next = 0;
	}
    
    /// Construct an attribute with a name and value.
	CAttribute( const char * _name, const char * _value )
	{
		name = _name;
		value = _value;
		document = 0;
		prev = next = 0;
	}

	const char*		Name()  const		{ return name.c_str (); }		///< Return the name of this attribute.
	const char*		Value() const		{ return value.c_str (); }		///< Return the value of this attribute.
	const int       IntValue() const;									///< Return the value of this attribute, converted to an integer.
	const double	DoubleValue() const;								///< Return the value of this attribute, converted to a double.

	/** QueryIntValue examines the value string. It is an alternative to the
		IntValue() method with richer error checking.
		If the value is an integer, it is stored in 'value' and 
		the call returns TIXML_SUCCESS. If it is not
		an integer, it returns TIXML_WRONG_TYPE.

		A specialized but useful call. Note that for success it returns 0,
		which is the opposite of almost all other TinyXml calls.
	*/
	int QueryIntValue( int* value ) const;
	/// QueryDoubleValue examines the value string. See QueryIntValue().
	int QueryDoubleValue( double* value ) const;

	void SetName( const char* _name )	{ name = _name; }				///< Set the name of this attribute.
	void SetValue( const char* _value )	{ value = _value; }				///< Set the value.

	void SetIntValue( int value );										///< Set the value from an integer.
	void SetDoubleValue( double value );								///< Set the value from a double.
/*
    #ifdef TIXML_USE_STL
	/// STL std::string form.
	void SetName( const std::string& _name )	
	{	
		StringToBuffer buf( _name );
		SetName ( buf.buffer ? buf.buffer : "error" );	
	}
	/// STL std::string form.	
	void SetValue( const std::string& _value )	
	{	
		StringToBuffer buf( _value );
		SetValue( buf.buffer ? buf.buffer : "error" );	
	}
	#endif
*/
	/// STL std::string form.
	void SetName( const std::string& _name )	
	{	
		StringToBuffer buf( _name );
		SetName ( buf.buffer ? buf.buffer : "error" );	
	}
	/// STL std::string form.	
	void SetValue( const std::string& _value )	
	{	
		StringToBuffer buf( _value );
		SetValue( buf.buffer ? buf.buffer : "error" );	
	}

	/// Get the next sibling attribute in the DOM. Returns null at end.
	CAttribute* Next() const;
	/// Get the previous sibling attribute in the DOM. Returns null at beginning.
	CAttribute* Previous() const;

	bool operator==( const CAttribute& rhs ) const { return rhs.name == name; }
	bool operator<( const CAttribute& rhs )	 const { return name < rhs.name; }
	bool operator>( const CAttribute& rhs )  const { return name > rhs.name; }

	/*	CAttribute parsing starts: first letter of the name
						 returns: the next char after the value end quote
	*/
	virtual const char* Parse( const char* p, ParsingData* data, Encoding encoding );

	// Prints this CAttribute to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	virtual void StreamOut( TIXML_OSTREAM * out ) const;
	// [internal use]
	// Set the document pointer so the attribute can report errors.
	void SetDocument( Document* doc )	{ document = doc; }

private:
	CAttribute( const CAttribute& );				// not implemented.
	void operator=( const CAttribute& base );	// not allowed.

	Document*	document;	// A pointer back to a document, for error reporting.
	TIXML_STRING name;
	TIXML_STRING value;
	CAttribute*	prev;
	CAttribute*	next;
};


/*	A class used to manage a group of attributes.
	It is only used internally, both by the ELEMENT and the DECLARATION.
	
	The set can be changed transparent to the Element and Declaration
	classes that use it, but NOT transparent to the CAttribute
	which has to implement a next() and previous() method. Which makes
	it a bit problematic and prevents the use of STL.

	This version is implemented with circular lists because:
		- I like circular lists
		- it demonstrates some independence from the (typical) doubly linked list.
*/
class TiXmlAttributeSet
{
public:
	TiXmlAttributeSet();
	~TiXmlAttributeSet();

	void Add( CAttribute* attribute );
	void Remove( CAttribute* attribute );

	CAttribute* First() const	{ return ( sentinel.next == &sentinel ) ? 0 : sentinel.next; }
	CAttribute* Last()  const	{ return ( sentinel.prev == &sentinel ) ? 0 : sentinel.prev; }
	CAttribute*	Find( const char * name ) const;

private:
	CAttribute sentinel;
};


/** The element is a container class. It has a value, the element name,
	and can contain other elements, text, comments, and unknowns.
	Elements also contain an arbitrary number of attributes.
*/
class Element : public CNode
{
public:
	/// Construct an element.
	Element (const char * in_value);
/*
	#ifdef TIXML_USE_STL
	/// std::string constructor.
	Element( const std::string& _value );
	#endif
*/
	/// std::string constructor.
	Element( const std::string& _value );

	Element( const Element& );

	void operator=( const Element& base );

	virtual ~Element();

	/** Given an attribute name, CAttribute() returns the value
		for the attribute of that name, or null if none exists.
	*/
	const char* Attribute( const char* name ) const;

	/** Given an attribute name, CAttribute() returns the value
		for the attribute of that name, or null if none exists.
		If the attribute exists and can be converted to an integer,
		the integer value will be put in the return 'i', if 'i'
		is non-null.
	*/
	const char* Attribute( const char* name, int* i ) const;

	/** Given an attribute name, CAttribute() returns the value
		for the attribute of that name, or null if none exists.
		If the attribute exists and can be converted to an double,
		the double value will be put in the return 'd', if 'd'
		is non-null.
	*/
	const char* Attribute( const char* name, double* d ) const;

	/** QueryIntAttribute examines the attribute - it is an alternative to the
		CAttribute() method with richer error checking.
		If the attribute is an integer, it is stored in 'value' and 
		the call returns TIXML_SUCCESS. If it is not
		an integer, it returns TIXML_WRONG_TYPE. If the attribute
		does not exist, then TIXML_NO_ATTRIBUTE is returned.
	*/	
	int QueryIntAttribute( const char* name, int* value ) const;
	/// QueryDoubleAttribute examines the attribute - see QueryIntAttribute().
	int QueryDoubleAttribute( const char* name, double* value ) const;

	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	void SetAttribute( const char* name, const char * value );

    //#ifdef TIXML_USE_STL
	const char* CAttribute( const std::string& name ) const				{ return CAttribute( name.c_str() ); }
	const char* CAttribute( const std::string& name, int* i ) const		{ return CAttribute( name.c_str(), i ); }
	const char* CAttribute( const std::string& name, double* d ) const	{ return CAttribute( name.c_str(), d ); }
	int QueryIntAttribute( const std::string& name, int* value ) const	{ return QueryIntAttribute( name.c_str(), value ); }
	int QueryDoubleAttribute( const std::string& name, double* value ) const { return QueryDoubleAttribute( name.c_str(), value ); }

	/// STL std::string form.
	void SetAttribute( const std::string& name, const std::string& _value )	
	{	
		StringToBuffer n( name );
		StringToBuffer v( _value );
		if ( n.buffer && v.buffer )
			SetAttribute (n.buffer, v.buffer );	
	}	
	///< STL std::string form.
	void SetAttribute( const std::string& name, int _value )	
	{	
		StringToBuffer n( name );
		if ( n.buffer )
			SetAttribute (n.buffer, _value);	
	}	
	//#endif

	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	void SetAttribute( const char * name, int value );

	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	void SetDoubleAttribute( const char * name, double value );

	/** Deletes an attribute with the given name.
	*/
	void RemoveAttribute( const char * name );
    //#ifdef TIXML_USE_STL
	void RemoveAttribute( const std::string& name )	{	RemoveAttribute (name.c_str ());	}	///< STL std::string form.
	//#endif

    tixml::CAttribute* FirstAttribute() const	{ return attributeSet.First(); }		///< Access the first attribute in this element.
	tixml::CAttribute* LastAttribute()	const 	{ return attributeSet.Last(); }		///< Access the last attribute in this element.

	/// Creates a new Element and returns it - the returned element is a copy.
	virtual CNode* Clone() const;
	// Print the Element to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	/*	Attribtue parsing starts: next char past '<'
						 returns: next char past '>'
	*/
	virtual const char* Parse( const char* p, ParsingData* data, Encoding encoding );

protected:

	void CopyTo( Element* target ) const;
	void ClearThis();	// like clear, but initializes 'this' object as well

	// Used to be public [internal use]
	//#ifdef TIXML_USE_STL
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	//#endif
	virtual void StreamOut( TIXML_OSTREAM * out ) const;

	/*	[internal use]
		Reads the "value" of the element -- another element, or text.
		This should terminate with the current end tag.
	*/
	const char* ReadValue( const char* in, ParsingData* prevData, Encoding encoding );

private:

	TiXmlAttributeSet attributeSet;
};


/**	An XML comment.
*/
class Comment : public CNode
{
public:
	/// Constructs an empty comment.
	Comment() : CNode( CNode::COMMENT ) {}
	Comment( const Comment& );
	void operator=( const Comment& base );

	virtual ~Comment()	{}

	/// Returns a copy of this Comment.
	virtual CNode* Clone() const;
	/// Write this Comment to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	/*	Attribtue parsing starts: at the ! of the !--
						 returns: next char past '>'
	*/
	virtual const char* Parse( const char* p, ParsingData* data, Encoding encoding );

protected:
	void CopyTo( Comment* target ) const;

	// used to be public
	//#ifdef TIXML_USE_STL
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	//#endif
	virtual void StreamOut( TIXML_OSTREAM * out ) const;

private:

};


/** XML text. Contained in an element.
*/
class Text : public CNode
{
	friend class Element;
public:
	/// Constructor.
	Text (const char * initValue) : CNode (CNode::TEXT)
	{
		SetValue( initValue );
	}
	virtual ~Text() {}

	//#ifdef TIXML_USE_STL
	/// Constructor.
	Text( const std::string& initValue ) : CNode (CNode::TEXT)
	{
		SetValue( initValue );
	}
	//#endif

	Text( const Text& copy ) : CNode( CNode::TEXT )	{ copy.CopyTo( this ); }
	void operator=( const Text& base )							 	{ base.CopyTo( this ); }

	/// Write this text object to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	virtual const char* Parse( const char* p, ParsingData* data, Encoding encoding );

protected :
	///  [internal use] Creates a new Element and returns it.
	virtual CNode* Clone() const;
	void CopyTo( Text* target ) const;

	virtual void StreamOut ( TIXML_OSTREAM * out ) const;
	bool Blank() const;	// returns true if all white space and new lines
	// [internal use]
	//#ifdef TIXML_USE_STL
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	//#endif

private:
};


/** In correct XML the declaration is the first entry in the file.
	@verbatim
		<?xml version="1.0" standalone="yes"?>
	@endverbatim

	TinyXml will happily read or write files without a declaration,
	however. There are 3 possible attributes to the declaration:
	version, encoding, and standalone.

	Note: In this version of the code, the attributes are
	handled as special cases, not generic attributes, simply
	because there can only be at most 3 and they are always the same.
*/
class Declaration : public CNode
{
public:
	/// Construct an empty declaration.
	Declaration()   : CNode( CNode::DECLARATION ) {}

//#ifdef TIXML_USE_STL
	/// Constructor.
	Declaration(	const std::string& _version,
						const std::string& _encoding,
						const std::string& _standalone );
//#endif

	/// Construct.
	Declaration(	const char* _version,
						const char* _encoding,
						const char* _standalone );

	Declaration( const Declaration& copy );
	void operator=( const Declaration& copy );

	virtual ~Declaration()	{}

	/// Version. Will return an empty string if none was found.
	const char *Version() const			{ return version.c_str (); }
	/// Encoding. Will return an empty string if none was found.
	const char *Encoding() const		{ return encoding.c_str (); }
	/// Is this a standalone document?
	const char *Standalone() const		{ return standalone.c_str (); }

	/// Creates a copy of this Declaration and returns it.
	virtual CNode* Clone() const;
	/// Print this declaration to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

    virtual const char* Parse( const char* p, ParsingData* data, tixml::Encoding encoding );

protected:
	void CopyTo( Declaration* target ) const;
	// used to be public
	//#ifdef TIXML_USE_STL
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	//#endif
	virtual void StreamOut ( TIXML_OSTREAM * out) const;

private:

	TIXML_STRING version;
	TIXML_STRING encoding;
	TIXML_STRING standalone;
};


/** Any tag that tinyXml doesn't recognize is saved as an
	unknown. It is a tag of text, but should not be modified.
	It will be written back to the XML, unchanged, when the file
	is saved.

	DTD tags get thrown into TiXmlUnknowns.
*/
class CUnknown : public CNode
{
public:
	CUnknown() : CNode( CNode::UNKNOWN )	{}
	virtual ~CUnknown() {}

	CUnknown( const CUnknown& copy ) : CNode( CNode::UNKNOWN )		{ copy.CopyTo( this ); }
	void operator=( const CUnknown& copy )										{ copy.CopyTo( this ); }

	/// Creates a copy of this CUnknown and returns it.
	virtual CNode* Clone() const;
	/// Print this CUnknown to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	virtual const char* Parse( const char* p, ParsingData* data, Encoding encoding );

protected:
	void CopyTo( CUnknown* target ) const;

	//#ifdef TIXML_USE_STL
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	//#endif
	virtual void StreamOut ( TIXML_OSTREAM * out ) const;

private:

};


/** Always the top level node. A document binds together all the
	XML pieces. It can be saved, loaded, and printed to the screen.
	The 'value' of a document node is the xml file name.
*/
class Document : public CNode
{
public:
	/// Create an empty document, that has no name.
	Document();
	/// Create a document with a name. The name of the document is also the filename of the xml.
	Document( const char * documentName );

	//#ifdef TIXML_USE_STL
	/// Constructor.
	Document( const std::string& documentName );
	//#endif

	Document( const Document& copy );
	void operator=( const Document& copy );

	virtual ~Document() {}

	/** Load a file using the current document value.
		Returns true if successful. Will delete any existing
		document data before loading.
	*/
	bool LoadFile( Encoding encoding = DEFAULT_ENCODING );
	/// Save a file using the current document value. Returns true if successful.
	bool SaveFile() const;
	/// Load a file using the given filename. Returns true if successful.
	bool LoadFile( const char * filename, Encoding encoding = DEFAULT_ENCODING );
	/// Save a file using the given filename. Returns true if successful.
	bool SaveFile( const char * filename ) const;

	//#ifdef TIXML_USE_STL
	bool LoadFile( const std::string& filename, Encoding encoding = DEFAULT_ENCODING )			///< STL std::string version.
	{
		StringToBuffer f( filename );
		return ( f.buffer && LoadFile( f.buffer, encoding ));
	}
	bool SaveFile( const std::string& filename ) const		///< STL std::string version.
	{
		StringToBuffer f( filename );
		return ( f.buffer && SaveFile( f.buffer ));
	}
	//#endif

	/** Parse the given null terminated block of xml data. Passing in an encoding to this
		method (either ENCODING_LEGACY or ENCODING_UTF8 will force TinyXml
		to use that encoding, regardless of what TinyXml might otherwise try to detect.
	*/
	virtual const char* Parse( const char* p, ParsingData* data = 0, Encoding encoding = DEFAULT_ENCODING );

	/** Get the root element -- the only top level element -- of the document.
		In well formed XML, there should only be one. TinyXml is tolerant of
		multiple elements at the document level.
	*/
	Element* RootElement() const		{ return FirstChildElement(); }

	/** If an error occurs, Error will be set to true. Also,
		- The ErrorId() will contain the integer identifier of the error (not generally useful)
		- The ErrorDesc() method will return the name of the error. (very useful)
		- The ErrorRow() and ErrorCol() will return the location of the error (if known)
	*/	
	bool Error() const						{ return error; }

	/// Contains a textual (english) description of the error if one occurs.
	const char * ErrorDesc() const	{ return errorDesc.c_str (); }

	/** Generally, you probably want the error string ( ErrorDesc() ). But if you
		prefer the ErrorId, this function will fetch it.
	*/
	const int ErrorId()	const				{ return errorId; }

	/** Returns the location (if known) of the error. The first column is column 1, 
		and the first row is row 1. A value of 0 means the row and column wasn't applicable
		(memory errors, for example, have no row/column) or the parser lost the error. (An
		error in the error reporting, in that case.)

		@sa SetTabSize, Row, Column
	*/
	int ErrorRow()	{ return errorLocation.row+1; }
	int ErrorCol()	{ return errorLocation.col+1; }	///< The column where the error occured. See ErrorRow()

	/** By calling this method, with a tab size
		greater than 0, the row and column of each node and attribute is stored
		when the file is loaded. Very useful for tracking the DOM back in to
		the source file.

		The tab size is required for calculating the location of nodes. If not
		set, the default of 4 is used. The tabsize is set per document. Setting
		the tabsize to 0 disables row/column tracking.

		Note that row and column tracking is not supported when using operator>>.

		The tab size needs to be enabled before the parse or load. Correct usage:
		@verbatim
		Document doc;
		doc.SetTabSize( 8 );
		doc.Load( "myfile.xml" );
		@endverbatim

		@sa Row, Column
	*/
	void SetTabSize( int _tabsize )		{ tabsize = _tabsize; }

	int TabSize() const	{ return tabsize; }

	/** If you have handled the error, it can be reset with this call. The error
		state is automatically cleared if you Parse a new XML block.
	*/
	void ClearError()						{	error = false; 
												errorId = 0; 
												errorDesc = ""; 
												errorLocation.row = errorLocation.col = 0; 
												//errorLocation.last = 0; 
											}

	/** Dump the document to standard out. */
	void Print() const						{ Print( stdout, 0 ); }

	/// Print this Document to a FILE stream.
	virtual void Print( FILE* cfile, int depth = 0 ) const;
	// [internal use]
	void SetError( int err, const char* errorLocation, ParsingData* prevData, Encoding encoding );

protected :
	virtual void StreamOut ( TIXML_OSTREAM * out) const;
	// [internal use]
	virtual CNode* Clone() const;
	//#ifdef TIXML_USE_STL
	    virtual void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag );
	//#endif

private:
	void CopyTo( Document* target ) const;

	bool error;
	int  errorId;
	TIXML_STRING errorDesc;
	int tabsize;
	Cursor errorLocation;
};


/**
	A Handle is a class that wraps a node pointer with null checks; this is
	an incredibly useful thing. Note that Handle is not part of the TinyXml
	DOM structure. It is a separate utility class.

	Take an example:
	@verbatim
	<Document>
		<Element attributeA = "valueA">
			<Child attributeB = "value1" />
			<Child attributeB = "value2" />
		</Element>
	<Document>
	@endverbatim

	Assuming you want the value of "attributeB" in the 2nd "Child" element, it's very 
	easy to write a *lot* of code that looks like:

	@verbatim
	Element* root = document.FirstChildElement( "Document" );
	if ( root )
	{
		Element* element = root->FirstChildElement( "Element" );
		if ( element )
		{
			Element* child = element->FirstChildElement( "Child" );
			if ( child )
			{
				Element* child2 = child->NextSiblingElement( "Child" );
				if ( child2 )
				{
					// Finally do something useful.
	@endverbatim

	And that doesn't even cover "else" cases. Handle addresses the verbosity
	of such code. A Handle checks for null	pointers so it is perfectly safe 
	and correct to use:

	@verbatim
	Handle docHandle( &document );
	Element* child2 = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", 1 ).Element();
	if ( child2 )
	{
		// do something useful
	@endverbatim

	Which is MUCH more concise and useful.

	It is also safe to copy handles - internally they are nothing more than node pointers.
	@verbatim
	Handle handleCopy = handle;
	@endverbatim

	What they should not be used for is iteration:

	@verbatim
	int i=0; 
	while ( true )
	{
		Element* child = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", i ).Element();
		if ( !child )
			break;
		// do something
		++i;
	}
	@endverbatim

	It seems reasonable, but it is in fact two embedded while loops. The Child method is 
	a linear walk to find the element, so this code would iterate much more than it needs 
	to. Instead, prefer:

	@verbatim
	Element* child = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).FirstChild( "Child" ).Element();

	for( child; child; child=child->NextSiblingElement() )
	{
		// do something
	}
	@endverbatim
*/
class Handle
{

private:
    tixml::CNode* node;

public:
	/// Create a handle from any node (at any depth of the tree.) This can be a null pointer.
	Handle( CNode* node )					{ this->node = node; }
	/// Copy constructor
	Handle( const Handle& ref )			{ this->node = ref.node; }
	Handle operator=( const Handle& ref ) { this->node = ref.node; return *this; }

	/// Return a handle to the first child node.
	Handle FirstChild() const;
	/// Return a handle to the first child node with the given name.
	Handle FirstChild( const char * value ) const;
	/// Return a handle to the first child element.
	Handle FirstChildElement() const;
	/// Return a handle to the first child element with the given name.
	Handle FirstChildElement( const char * value ) const;

	/** Return a handle to the "index" child with the given name. 
		The first child is 0, the second 1, etc.
	*/
	Handle Child( const char* value, int index ) const;
	/** Return a handle to the "index" child. 
		The first child is 0, the second 1, etc.
	*/
	Handle Child( int index ) const;
	/** Return a handle to the "index" child element with the given name. 
		The first child element is 0, the second 1, etc. Note that only TiXmlElements
		are indexed: other types are not counted.
	*/
	Handle ChildElement( const char* value, int index ) const;
	/** Return a handle to the "index" child element. 
		The first child element is 0, the second 1, etc. Note that only TiXmlElements
		are indexed: other types are not counted.
	*/
	Handle ChildElement( int index ) const;

	//#ifdef TIXML_USE_STL
	Handle FirstChild( const std::string& _value ) const				{ return FirstChild( _value.c_str() ); }
	Handle FirstChildElement( const std::string& _value ) const		{ return FirstChildElement( _value.c_str() ); }

	Handle Child( const std::string& _value, int index ) const			{ return Child( _value.c_str(), index ); }
	Handle ChildElement( const std::string& _value, int index ) const	{ return ChildElement( _value.c_str(), index ); }
	//#endif

	/// Return the handle as a CNode. This may return null.
	tixml::CNode* Node() const			{ return node; } 
	/// Return the handle as a Element. This may return null.
	tixml::Element* Element() const	{ return ( ( node && node->ToElement() ) ? node->ToElement() : 0 ); }
	/// Return the handle as a Text. This may return null.
	tixml::Text* Text() const			{ return ( ( node && node->ToText() ) ? node->ToText() : 0 ); }
	/// Return the handle as a CUnknown. This may return null;
	tixml::CUnknown* CUnknown() const			{ return ( ( node && node->ToUnknown() ) ? node->ToUnknown() : 0 ); }
};

}; //namespace tixml

#endif

