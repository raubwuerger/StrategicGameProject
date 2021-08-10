#include "stdafx.h"
#include "GameMapFactory.h"
#include "GameMapCreatorSimple.h"

GameMapFactory::GameMapFactory()
	: TheGameMap(nullptr)
{
}

GameMapFactory::~GameMapFactory()
{
}

GameMapRepository* GameMapFactory::CreateModelMap()
{
	MapCreator = new GameMapCreatorSimple;
	MapCreator->CreateMap();
	return TheGameMap;
}
