#include "stdafx.h"
#include "EditorController.h"
#include "map\MapView.h"
#include "connectors\ConnectorMapHexItem.h"
#include "connectors\ConnectorMapUnitItem.h"
#include "editors\TerrainTypeEditor.h"
#include "editors/UnitTypeEditor.h"

EditorController::EditorController(MapView *mapView)
	:MapViewInstance(mapView)
{

}

void EditorController::Activate(TerrainTypeEditor* terrainTypeEditor)
{
	DisconnectAll();
	QObject::connect(MapViewInstance->ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemPressedLeftButton, terrainTypeEditor, &TerrainTypeEditor::SlotChangeTerrainTypeHexItem);
}

void EditorController::Activate(UnitTypeEditor* unitTypeEditor)
{
	DisconnectAll();
	QObject::connect(MapViewInstance->ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemPressedLeftButton, unitTypeEditor, &UnitTypeEditor::SlotAddUnit);
	QObject::connect(MapViewInstance->ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemPressedRightButton, unitTypeEditor, &UnitTypeEditor::SlotDeleteUnitFromMapHexItemId);
	QObject::connect(MapViewInstance->ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedRightButton, unitTypeEditor, &UnitTypeEditor::SlotDeleteUnitFromGameUnitId);

}

void EditorController::Activate(OwnerTypeEditor* ownerTypeEditor)
{
	int whatToDo = 1;
	//TODO: What to do?
}

void EditorController::DisconnectAll()
{
	QObject::disconnect(MapViewInstance->ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemPressedLeftButton, TerrainTypeEditorInstance, &TerrainTypeEditor::SlotChangeTerrainTypeHexItem);

	QObject::disconnect(MapViewInstance->ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemPressedLeftButton, UnitTypeEditorInstance, &UnitTypeEditor::SlotAddUnit);
	QObject::disconnect(MapViewInstance->ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemPressedRightButton, UnitTypeEditorInstance, &UnitTypeEditor::SlotDeleteUnitFromMapHexItemId);
	QObject::disconnect(MapViewInstance->ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedRightButton, UnitTypeEditorInstance, &UnitTypeEditor::SlotDeleteUnitFromGameUnitId);
}
