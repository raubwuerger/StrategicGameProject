// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#pragma once
#include <string>

namespace jha
{

class StringHelper
{
public:
/** Constructor */
	StringHelper();
/** */
	std::string ConvertFromInt( int value ) const;
/** */
	std::string ConvertFromInt64( LONGLONG value ) const;
public:
	static const std::wstring EMPTY;
};


}


