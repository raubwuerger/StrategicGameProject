#include "stdafx.h"
#include "CreateNewMap.h"
#include "GameFactory.h"
#include "model/GameDataConfig.h"

CreateNewMap::CreateNewMap(QObject *parent)
	: QObject(parent)
{
}

CreateNewMap::~CreateNewMap()
{

}

void CreateNewMap::DoCreateNewMap()
{
	//TODO: Get values from Dialog ...
	GameMapConfig::GetInstance()->Cols = 60;
	GameMapConfig::GetInstance()->Rows = 120;
	GameFactory::GetInstance()->CreateNewGame();

}
