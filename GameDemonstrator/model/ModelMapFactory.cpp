#include "stdafx.h"
#include "ModelMapFactory.h"
#include "ModelMapCreatorSimple.h"

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

ModelMapRepository* ModelMapFactory::CreateModelMap()
{
	MapCreator = new ModelMapCreatorSimple;
	MapCreator->CreateMap();
	return TheGameMap;
}
