#include "stdafx.h"
#include "ModelMapConfigFactory.h"
#include "GameMap.h"
#include "ModelMapConfig.h"

ModelMapConfigFactory* ModelMapConfigFactory::Instance = nullptr; 

ModelMapConfigFactory* ModelMapConfigFactory::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new ModelMapConfigFactory;
	return Instance;
}

void ModelMapConfigFactory::Release()
{
	delete Instance;
	Instance = nullptr;
}

ModelMapConfigFactory::ModelMapConfigFactory()
	: TheGameMap(nullptr)
{
}

ModelMapConfigFactory::~ModelMapConfigFactory()
{
	delete TheGameMap;
	TheGameMap = nullptr;
}

GameMap* ModelMapConfigFactory::CreateMap()
{
	TheGameMap = new GameMap();
	TheGameMap->Init( ModelMapConfig::GetInstance()->Rows, ModelMapConfig::GetInstance()->Cols );
	return TheGameMap;
}
