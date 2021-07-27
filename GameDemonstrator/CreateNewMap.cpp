#include "stdafx.h"
#include "CreateNewMap.h"
#include "CreateNewMapDialog.h"
#include "MapView.h"
#include "GameInitialisationData.h"
#include "GameFactory.h"
#include "model/GameDataConfig.h"

CreateNewMap::CreateNewMap(QObject *parent)
	: QObject(parent),
	MapView(nullptr),
	DefaultTerrainType(nullptr),
	GameData(nullptr)
{
	GameData = new GameInitialisationData;
}

CreateNewMap::~CreateNewMap()
{

}

void CreateNewMap::DoCreateNewMap()
{
/*	GameDataConfig::GetInstance()->TheGameMapConfig.Cols = 60;
	GameDataConfig::GetInstance()->TheGameMapConfig.Rows = 120;
	CGameFactory().CreateNewGame();
*/
/*
	Q_ASSERT(GameData);
	CreateNewMapDialog dialog(nullptr);
	if( dialog.exec() == QDialog::Rejected )
	{
		return;
	}

	GameData->Cols = dialog.GetTilesX();
	GameData->Rows = dialog.GetTilesY();
*/
	GameData->Cols = 60;
	GameData->Rows = 120;
	GameFactory().CreateNewGame( *GameData, MapView, DefaultTerrainType );

}
