#include "stdafx.h"
#include "GameMapItemFactory.h"
#include "io\GameMapItemCreatorSimple.h"

GameMapItemFactory::GameMapItemFactory()
	: TheGameMap(nullptr)
{
}

GameMapItemFactory::~GameMapItemFactory()
{
}

bool GameMapItemFactory::Create()
{
	MapCreator = new GameMapItemCreatorSimple;
	return MapCreator->CreateMap();
}
