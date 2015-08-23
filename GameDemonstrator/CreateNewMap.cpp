#include "stdafx.h"
#include "CreateNewMap.h"
#include "CreateNewMapDialog.h"
#include "MapView.h"

CCreateNewMap::CCreateNewMap(QObject *parent)
	: QObject(parent),
	m_MapView(nullptr),
	m_TerrainTypeRepository(nullptr)
{

}

CCreateNewMap::~CCreateNewMap()
{

}

void CCreateNewMap::DoCreateNewMap()
{
	CreateNewMapDialog dialog(nullptr);
	if( dialog.exec() == QDialog::Rejected )
	{
		return;
	}
	m_MapView->Init( dialog.GetTilesX(), dialog.GetTilesY(), m_TerrainTypeRepository );
}
