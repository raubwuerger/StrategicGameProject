// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#pragma once
#include <memory>
#include <vector>
#include "File.h"

namespace jha
{

class Directory
{           
public:
	typedef std::unique_ptr<Directory> unique;
	typedef std::shared_ptr<Directory> shared;
	typedef std::weak_ptr<Directory> weak;
public:
/** Constructor */
	Directory( const std::wstring& path );
/** Fügt neue Datei hinzu */
	void AddFile( File::unique file );
/** Fügt neues Verzeichniss hinzu */
	void AddDirectory( Directory::unique directory );
/** Liefert Verzeichnisse */
	const std::vector<Directory::unique>& GetDirectories() const;
/** Get m_Files */
	const std::vector<File::unique>& GetFiles() const;
/** Get m_Parent */
	const Directory* GetParent() const { return m_Parent; }
/** Set m_Parent */
	void SetParent( Directory* val) { m_Parent = val; }
/** Get m_Path */
	const std::wstring& GetPath() const { return m_Path; }
/** Berechnet Anzahl Dateien */
	int CalculateFileCount() const;
/** */
	Directory* FindDirectoryByName( const std::wstring& path ) const;
private:
	std::vector<Directory::unique>	m_Directories;	
	std::vector<File::unique>	m_Files;
	Directory*	m_Parent;
	std::wstring	m_Path;
};


}






