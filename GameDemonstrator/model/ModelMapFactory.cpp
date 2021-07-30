#include "stdafx.h"
#include "ModelMapFactory.h"
#include "ModelMapRepository.h"
#include "ModelMapConfig.h"

ModelMapFactory* ModelMapFactory::Instance = nullptr; 

ModelMapFactory* ModelMapFactory::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new ModelMapFactory;
	return Instance;
}

void ModelMapFactory::Release()
{
	delete Instance;
	Instance = nullptr;
}

ModelMapFactory::ModelMapFactory()
	: TheGameMap(nullptr)
{
}

ModelMapFactory::~ModelMapFactory()
{
	delete TheGameMap;
	TheGameMap = nullptr;
}

ModelMapRepository* ModelMapFactory::CreateMap()
{
	TheGameMap = new ModelMapRepository();
	return TheGameMap;
}
