#include "stdafx.h"
#include "GameFactory.h"
#include "GameMapFactory.h"
#include "io\SerializerFactory.h"
#include "io\SerializerGame.h"

GameFactory::GameFactory()
{

}

bool GameFactory::Create(const GameConfig* gameConfig)
{
	GameMapFactory factory;
	factory.Create();
	return true;
}

bool GameFactory::CreateFromSavegame()
{
	return SerializerFactory().CreateInterface()->LoadGame();
}
