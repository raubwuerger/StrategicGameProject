// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "Directory.h"

namespace jha
{

//=================================================================================================
Directory::Directory(const std::wstring& path)
	: m_Path(path),
	m_Parent(nullptr)
{
	m_Directories.reserve(100);
	m_Files.reserve(10000);
}

//=================================================================================================
void Directory::AddFile( File::unique file )
{
	m_Files.push_back( std::move(file) );
}

//=================================================================================================
void Directory::AddDirectory( Directory::unique directory )
{
	m_Directories.push_back( std::move(directory) );
}

//=================================================================================================
const std::vector<Directory::unique>& Directory::GetDirectories() const
{
	return m_Directories;
}

//=================================================================================================
const std::vector<File::unique>& Directory::GetFiles() const
{
	return m_Files;
}

//=================================================================================================
int Directory::CalculateFileCount() const
{
	size_t fileCount = 0;
	fileCount += m_Files.size();
	for( size_t i=0;i<m_Directories.size();i++ )
	{
		fileCount += m_Directories.at(i)->CalculateFileCount();
	}

	return static_cast<int>(fileCount);
}

//=================================================================================================
Directory* Directory::FindDirectoryByName( const std::wstring& path ) const
{
	if( path == m_Path )
	{
		//TODO: Das ist bestimmt keine gute Idee! Prüfen!!
		return const_cast<Directory*>(this);
	}
	//TODO: Sorted Vector erstellen und binär suchen (lower_bound)
	for( size_t i=0;i<m_Directories.size();i++ )
	{
		Directory *subDirectory = m_Directories.at(i)->FindDirectoryByName(path);
		if( subDirectory != nullptr )
		{
			return subDirectory;
		}
	}
	return nullptr;
}

}
