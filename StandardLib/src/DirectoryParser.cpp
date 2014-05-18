// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "DirectoryParser.h"
#include "File.h"
#include <stack>
#include <iostream>


namespace jha
{

//=================================================================================================
DirectoryParser::DirectoryParser(int estimedFiles)
	: m_EstimatedFiles(estimedFiles)
{
}

//=================================================================================================
std::vector<jha::File> DirectoryParser::ParseRecursive( const std::wstring& path ) const 
{
	std::vector<jha::File> result;
	CFileFind finder;

	// build a string with wildcards
	CString strWildcard(path.c_str());
	strWildcard += _T("\\*.*");

	// start working for files
	BOOL anyMoreFiles = finder.FindFile(strWildcard);
	while(anyMoreFiles)
	{
		anyMoreFiles = finder.FindNextFile();
		if( finder.IsDots() == TRUE )
		{
			continue;
		}

		CString filePath = finder.GetFilePath();
		if( finder.IsDirectory() == TRUE )
		{
			std::vector<jha::File> subResult = ParseRecursive(filePath.GetString());
			result.insert( result.end(), subResult.begin(), subResult.end() );
		}

		CString fileName = finder.GetFileName();
		result.push_back( jha::File( fileName.GetString(), filePath.GetString() ) );
	}

	finder.Close();
	return result;
}

std::vector<jha::File::unique> DirectoryParser::CreateFlatFileList( const std::wstring& rootPath, const std::wstring& mask ) const
{
	std::vector<jha::File::unique> result;
	result.reserve(m_EstimatedFiles);
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	std::wstring spec;
	std::stack<std::wstring> directories;

	directories.push(rootPath);

	while(!directories.empty()) 
	{
		const std::wstring currentPath = directories.top();
		spec = currentPath + L"\\" + mask;
		directories.pop();

		hFind = FindFirstFile(spec.c_str(), &ffd);
		if (hFind == INVALID_HANDLE_VALUE)  
		{
			return result;
		} 

		do{
			if (wcscmp(ffd.cFileName, L".") != 0 && wcscmp(ffd.cFileName, L"..") != 0) 
			{
				if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				{
					directories.push(currentPath + L"\\" + ffd.cFileName);
				}
				else 
				{
					result.push_back( jha::File::unique( new jha::File( ffd.cFileName, currentPath ) ) );
				}
			}
		} while (FindNextFile(hFind, &ffd) != 0);

		if (GetLastError() != ERROR_NO_MORE_FILES) 
		{
			FindClose(hFind);
			return result;
		}

		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
	}

	return result;
}

Directory* DirectoryParser::CreateStructuredList( const std::wstring& rootPath, const std::wstring& mask /*= _T("*.*") */ ) const
{
	Directory* result = new Directory(rootPath);
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	std::wstring spec;
	std::stack<std::wstring> directories;
	Directory* currentDirectory = nullptr;
	directories.push(rootPath);

	while( directories.empty() == false ) 
	{
		const std::wstring currentPath = directories.top();
		spec = currentPath + L"\\" + mask;
		directories.pop();

		currentDirectory = result->FindDirectoryByName(currentPath);
		if( currentDirectory == nullptr )
		{
			ASSERT(false);
		}

		hFind = FindFirstFile(spec.c_str(), &ffd);
		if (hFind == INVALID_HANDLE_VALUE)  
		{
			return result;
		} 

		do{
			if( wcscmp(ffd.cFileName, L".") != 0 && wcscmp(ffd.cFileName, L"..") != 0 ) 
			{
				if( ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) 
				{
					std::wstring subDirectoryPath = currentPath + L"\\" + ffd.cFileName;
					directories.push(subDirectoryPath);
					jha::Directory::unique subDirectory( new Directory(subDirectoryPath) );
					currentDirectory->AddDirectory( std::move(subDirectory) );
				}
				else 
				{
					currentDirectory->AddFile( jha::File::unique( new jha::File( ffd.cFileName, currentPath ) ) );
				}
			}
		} while (FindNextFile(hFind, &ffd) != 0);

		if (GetLastError() != ERROR_NO_MORE_FILES) 
		{
			FindClose(hFind);
			return result;
		}

		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
	}

	return result;
}

}




