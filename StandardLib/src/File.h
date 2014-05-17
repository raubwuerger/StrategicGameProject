// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#pragma once
#include <string>
#include "StringHelper.h"

namespace jha
{

class File
{
public:
/** Constructor */
	File( const std::wstring& name, const std::wstring& path = StringHelper::EMPTY );
/** */
	const std::wstring& GetName() const;
/** */
	const std::wstring& Path() const;
private:
	std::wstring m_Name;
	std::wstring m_Path;
};


}




