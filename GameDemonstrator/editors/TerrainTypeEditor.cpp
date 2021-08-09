#include "stdafx.h"
#include "TerrainTypeEditor.h"
#include "map/MapEventManager.h"
#include "map/MapHexItem.h"
#include "model/ModelTerrainType.h"
#include "model/ModelTerrainTypeRepository.h"

TerrainTypeEditor::TerrainTypeEditor(QObject *parent)
	: QObject(parent),
	ActiveTerrainType(nullptr),
	MapEventManagerInstance(nullptr)
{

}

TerrainTypeEditor::~TerrainTypeEditor()
{

}

void TerrainTypeEditor::SetMapEventManager(MapEventManager* mapeventManager)
{
	MapEventManagerInstance = mapeventManager;
}

void TerrainTypeEditor::ActivateTerrainType( int terrainTypeId )
{
	ActiveTerrainType = ModelTerrainTypeRepository::GetInstance()->FindTerrainTypeById( terrainTypeId );
}

void TerrainTypeEditor::ChangeTerrainTypeHexItem( int row, int col )
{
	Q_ASSERT(ModelTerrainTypeRepository::GetInstance());
	Q_ASSERT(MapEventManagerInstance);
	if( ActiveTerrainType == nullptr )
	{
		return;
	}

	MapHexItem *item = MapEventManagerInstance->FindItemByIndexNonConst(row, col);
	if( item == nullptr )
	{
		return;
	}
	item->SetTerrainImage( ActiveTerrainType->GetImage() );
	emit TerrainTypeChanged( item->GetModelMapItemId(), ActiveTerrainType->GetId() );
}
