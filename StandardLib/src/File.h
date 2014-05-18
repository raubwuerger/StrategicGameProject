// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#pragma once
#include <string>
#include "StringHelper.h"
#include <memory>

namespace jha
{

class File
{
public:
	typedef std::unique_ptr<File> unique;
	typedef std::shared_ptr<File> shared;
	typedef std::weak_ptr<File> weak;
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




