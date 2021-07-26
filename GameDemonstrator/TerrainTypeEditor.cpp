#include "stdafx.h"
#include "TerrainTypeEditor.h"
#include "MapEventManager.h"
#include "TerrainTypeRepository.h"
#include "MapEventManager.h"
#include "TerrainType.h"
#include "MapViewHexItem.h"

CTerrainTypeEditor::CTerrainTypeEditor(QObject *parent)
	: QObject(parent),
	ActiveTerrainType(nullptr),
	MapEventManager(nullptr)
{

}

CTerrainTypeEditor::~CTerrainTypeEditor()
{

}

void CTerrainTypeEditor::ActivateTerrainType( int terrainTypeId )
{
	ActiveTerrainType = CTerrainTypeRepository::GetInstance()->FindTerrainTypeById( terrainTypeId );
}

void CTerrainTypeEditor::ChangeTerrainTypeHexItem( int row, int col )
{
	Q_ASSERT(CTerrainTypeRepository::GetInstance());
	Q_ASSERT(MapEventManager);
	if( ActiveTerrainType == nullptr )
	{
		return;
	}

	MapViewHexItem *item = MapEventManager->FindItemByIndexNonConst( row, col );
	if( item == nullptr )
	{
		return;
	}
	item->SetTerrainImage( ActiveTerrainType->GetImage() );
}
