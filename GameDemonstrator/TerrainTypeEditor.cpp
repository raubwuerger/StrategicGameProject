#include "stdafx.h"
#include "TerrainTypeEditor.h"
#include "MapEventManager.h"
#include "model/ModelTerrainTypeRepository.h"
#include "MapEventManager.h"
#include "model/ModelTerrainType.h"
#include "MapHexItem.h"

TerrainTypeEditor::TerrainTypeEditor(QObject *parent)
	: QObject(parent),
	ActiveTerrainType(nullptr),
	MapEventManager(nullptr)
{

}

TerrainTypeEditor::~TerrainTypeEditor()
{

}

void TerrainTypeEditor::ActivateTerrainType( int terrainTypeId )
{
	ActiveTerrainType = ModelTerrainTypeRepository::GetInstance()->FindTerrainTypeById( terrainTypeId );
}

void TerrainTypeEditor::ChangeTerrainTypeHexItem( int row, int col )
{
	Q_ASSERT(ModelTerrainTypeRepository::GetInstance());
	Q_ASSERT(MapEventManager);
	if( ActiveTerrainType == nullptr )
	{
		return;
	}

	MapHexItem *item = MapEventManager->FindItemByIndexNonConst( row, col );
	if( item == nullptr )
	{
		return;
	}
	item->SetTerrainImage( ActiveTerrainType->GetImage() );
	emit TerrainTypeChanged( item->GetModelMapItemId(), ActiveTerrainType->GetId() );
}
