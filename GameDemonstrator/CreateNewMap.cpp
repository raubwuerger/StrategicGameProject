#include "stdafx.h"
#include "CreateNewMap.h"
#include "CreateNewMapDialog.h"
#include "MapView.h"
#include "GameInitialisationData.h"
#include "GameFactory.h"

CCreateNewMap::CCreateNewMap(QObject *parent)
	: QObject(parent),
	MapView(nullptr),
	DefaultTerrainType(nullptr),
	GameData(nullptr)
{
	GameData = new GDModel::CGameInitialisationData;
}

CCreateNewMap::~CCreateNewMap()
{

}

void CCreateNewMap::DoCreateNewMap()
{
	Q_ASSERT(GameData);
	CreateNewMapDialog dialog(nullptr);
	if( dialog.exec() == QDialog::Rejected )
	{
		return;
	}

	GameData->Cols = dialog.GetTilesX();
	GameData->Rows = dialog.GetTilesY();

	CGameFactory().CreateNewGame( *GameData, MapView, DefaultTerrainType );
}
