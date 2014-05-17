// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "File.h"

namespace jha
{

//=================================================================================================
File::File( const std::wstring& name, const std::wstring& path )
	: m_Name(name),
	m_Path(path)
{
}

//=================================================================================================
const std::wstring& File::GetName() const
{
	return m_Name;
}

//=================================================================================================
const std::wstring& File::Path() const
{
	return m_Path;
}

}




