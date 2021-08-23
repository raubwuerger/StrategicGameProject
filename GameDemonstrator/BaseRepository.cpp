#include "stdafx.h"
#include "BaseRepository.h"
#include "RepositoryCleaner.h"

BaseRepository::BaseRepository()
{
	RepositoryCleaner::GetInstance()->Register(this);
}
