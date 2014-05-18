// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#pragma once
#include <vector>
#include <string>
#include "File.h"
#include "Directory.h"

namespace jha
{

class File;

class DirectoryParser
{
public:
/** */
	DirectoryParser( int estimedFiles = 200000 );
/** */
	std::vector<jha::File> ParseRecursive( const std::wstring& path ) const;
/** */
	std::vector<jha::File::unique> CreateFlatFileList( const std::wstring& path, const std::wstring& mask = _T("*.*") ) const;
/** */
	Directory* CreateStructuredList( const std::wstring& path, const std::wstring& mask = _T("*.*") ) const;
private:
	int	m_EstimatedFiles;
};


}




