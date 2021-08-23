#include "stdafx.h"
#include "TerrainTypeEditor.h"
#include "map/MapHexItemEventManager.h"
#include "map/MapHexItem.h"
#include "model/ModelTerrainType.h"
#include "model/ModelTerrainTypeRepository.h"
#include "game/GameMapItemRepository.h"
#include "game/GameMapItem.h"
#include "controller/EditorController.h"
#include "LogInterface.h"

TerrainTypeEditor::TerrainTypeEditor(QObject *parent)
	: BaseEditor(parent),
	ActiveTerrainType(nullptr),
	MapEventManagerInstance(nullptr),
	EditorControllerInstance(nullptr)
{

}

TerrainTypeEditor::~TerrainTypeEditor()
{

}

void TerrainTypeEditor::SetMapEventManager(MapHexItemEventManager* mapeventManager)
{
	MapEventManagerInstance = mapeventManager;
}

void TerrainTypeEditor::SetEditorController(EditorController* editorController)
{
	EditorControllerInstance = editorController;
}

void TerrainTypeEditor::SlotActivateTerrainType( int terrainTypeId )
{
	ActiveTerrainType = ModelTerrainTypeRepository::GetInstance()->FindTerrainTypeById( terrainTypeId );
}

void TerrainTypeEditor::SlotChangeTerrainTypeHexItem(int gameMapItemId)
{
	Q_ASSERT(MapEventManagerInstance);
	if( ActiveTerrainType == nullptr )
	{
		return;
	}

	MapHexItem *item = MapEventManagerInstance->FindMapHexItem(gameMapItemId);
	if( item == nullptr )
	{
		return;
	}
	item->SetTerrainImage( ActiveTerrainType->GetImage() );

	GameMapItem *modelMapToUpdate = GameMapItemRepository::GetInstance()->GetGameMapItemById(item->GetGameMapItemId());
	if (nullptr == modelMapToUpdate)
	{
		jha::GetLog()->Log_DEBUG(tr("ModelMapItem with Id=%1 not found!").arg(QString::number(item->GetGameMapItemId())));
		return;
	}

	modelMapToUpdate->SetModelTerrainType(ActiveTerrainType);
}

void TerrainTypeEditor::SlotActivated()
{
	if (nullptr == EditorControllerInstance)
	{
		return;
	}
	EditorControllerInstance->Activate(this);
}
