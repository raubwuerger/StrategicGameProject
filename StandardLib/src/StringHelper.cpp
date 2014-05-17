// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "StringHelper.h"
#include <sstream>

namespace jha
{

const std::wstring StringHelper::EMPTY = _T("");

//=================================================================================================
StringHelper::StringHelper()
{
}

//=================================================================================================
std::string StringHelper::ConvertFromInt( int value ) const
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

//=================================================================================================
std::string StringHelper::ConvertFromInt64( LONGLONG value ) const
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

}


