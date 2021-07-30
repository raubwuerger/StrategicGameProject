#include "stdafx.h"
#include "CreateNewMap.h"
#include "game/GameFactory.h"
#include "model/ModelDataOverallSettings.h"

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
	ModelMapConfig::GetInstance()->Cols = 60;
	ModelMapConfig::GetInstance()->Rows = 120;
	GameFactory::GetInstance()->CreateNewGame();

}
