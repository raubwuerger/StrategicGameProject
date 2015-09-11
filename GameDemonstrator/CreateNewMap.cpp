#include "stdafx.h"
#include "CreateNewMap.h"
#include "CreateNewMapDialog.h"
#include "MapView.h"
#include "GameInitialisationData.h"
#include "GameFactory.h"

CCreateNewMap::CCreateNewMap(QObject *parent)
	: QObject(parent),
	m_MapView(nullptr),
	m_DefaultTerrainType(nullptr),
	m_GameData(nullptr)
{
	m_GameData = new GDModel::CGameInitialisationData;
}

CCreateNewMap::~CCreateNewMap()
{

}

void CCreateNewMap::DoCreateNewMap()
{
	Q_ASSERT(m_GameData);
	CreateNewMapDialog dialog(nullptr);
	if( dialog.exec() == QDialog::Rejected )
	{
		return;
	}

	m_GameData->Cols = dialog.GetTilesX();
	m_GameData->Rows = dialog.GetTilesY();

	CGameFactory().CreateNewGame( *m_GameData, m_MapView, m_DefaultTerrainType );
}
