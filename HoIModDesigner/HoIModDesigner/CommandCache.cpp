#include "stdafx.h"
#include "CommandCache.h"


void CommandCache::AddCommand( jha::Command *command )
{
	if( FindCommand(command) != nullptr )
	{
		return;
	}
	m_CommandCache.append(command);
}

jha::Command* CommandCache::FindCommand( jha::Command *command )
{
	if( command == nullptr )
	{
		return nullptr;
	}
	int indexFound = m_CommandCache.indexOf(command);
	if( indexFound == -1 )
	{
		return nullptr;
	}
	return m_CommandCache.at(indexFound);
}

void CommandCache::ClearCommandCache()
{
	for( int i=0;i<m_CommandCache.size(); i++ )
	{
		delete m_CommandCache.at(i);
	}
	m_CommandCache.clear();
}
