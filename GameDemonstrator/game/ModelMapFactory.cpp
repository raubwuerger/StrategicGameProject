#include "stdafx.h"
#include "ModelMapFactory.h"
#include "ModelMapCreatorSimple.h"

ModelMapFactory::ModelMapFactory()
	: TheGameMap(nullptr)
{
}

ModelMapFactory::~ModelMapFactory()
{
}

ModelMapRepository* ModelMapFactory::CreateModelMap()
{
	MapCreator = new ModelMapCreatorSimple;
	MapCreator->CreateMap();
	return TheGameMap;
}
