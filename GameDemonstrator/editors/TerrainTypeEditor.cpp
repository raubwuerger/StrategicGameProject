#include "stdafx.h"
#include "TerrainTypeEditor.h"
#include "map/MapHexItemEventManager.h"
#include "map/MapHexItem.h"
#include "model/ModelTerrainType.h"
#include "model/ModelTerrainTypeRepository.h"
#include "game/GameMapTileRepository.h"
#include "game/GameMapTile.h"
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

void TerrainTypeEditor::SlotDeactivated()
{
	return; //TODO: Do nothing at the moment
}

void TerrainTypeEditor::SlotActivateTerrainType( int terrainTypeId )
{
	ActiveTerrainType = ModelTerrainTypeRepository::GetInstance()->GetById( terrainTypeId );
}

#include "game/GameUnitRepository.h"
#include "game/GameUnit.h"
#include "controller/TerrainAccessTester.h"
void TerrainTypeEditor::SlotChangeTerrainTypeHexItem(int gameMapItemId)
{
	if (false == BaseEditor::GetActive())
	{
		return;
	}

	Q_ASSERT(MapEventManagerInstance);
	if( ActiveTerrainType == nullptr )
	{
		return;
	}

	if (false == IsTerrainTypeValid(gameMapItemId))
	{
		return;
	}

	MapHexItem *item = MapEventManagerInstance->FindMapHexItem(gameMapItemId);
	if( item == nullptr )
	{
		return;
	}
	item->SetTerrainImage( ActiveTerrainType->GetImage() );

	GameMapTile *gameMapItemToUpdate = GameMapTileRepository::GetInstance()->GetById(item->GetId());
	if (nullptr == gameMapItemToUpdate)
	{
		jha::GetLog()->Log_DEBUG(tr("ModelMapItem with Id=%1 not found!").arg(QString::number(item->GetId())));
		return;
	}

	gameMapItemToUpdate->SetModelTerrainType(ActiveTerrainType);
}

bool TerrainTypeEditor::IsTerrainTypeValid(int gameMapItemId) const
{
	const GameUnit* gameUnit = GameUnitRepository::GetInstance()->GetByGameMapTileId(gameMapItemId);
	if (nullptr == gameUnit)
	{
		return true; //No GameUnit is on MapItem
	}

	return TerrainAccessTester::Accessable(gameUnit, ActiveTerrainType);
}

void TerrainTypeEditor::SlotActivated()
{
	if (nullptr == EditorControllerInstance)
	{
		return;
	}
	EditorControllerInstance->Activate(this);
}
