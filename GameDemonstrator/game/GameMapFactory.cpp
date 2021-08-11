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

bool GameMapFactory::Create()
{
	MapCreator = new GameMapCreatorSimple;
	return MapCreator->CreateMap();
}
