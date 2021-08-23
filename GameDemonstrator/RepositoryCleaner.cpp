#include "stdafx.h"
#include "RepositoryCleaner.h"
#include "BaseRepository.h"

RepositoryCleaner* RepositoryCleaner::Instance = nullptr;

RepositoryCleaner* RepositoryCleaner::GetInstance()
{
	if (nullptr != Instance)
	{
		return Instance;
	}

	Instance = new RepositoryCleaner;
	return Instance;
}

void RepositoryCleaner::Register(BaseRepository* baseRepository)
{
	if (true == Repositories.contains(baseRepository))
	{
		return;
	}

	Repositories.push_back(baseRepository);
}

void RepositoryCleaner::ReleaseAll()
{
	QVectorIterator< BaseRepository* > current(Repositories);
	while (current.hasNext())
	{
		current.next()->Release();
	}

	Repositories.clear();
}
