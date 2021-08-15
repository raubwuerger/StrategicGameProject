#include "stdafx.h"
#include "EditorController.h"

EditorController::EditorController(MapView *mapView)
	:MapViewInstance(mapView)
{

}

void EditorController::Activate(TerrainTypeEditor* terrainTypeEditor)
{
	QString iAmHere;
}

void EditorController::Activate(UnitTypeEditor* unitTypeEditor)
{
	QString iAmHere;
}

void EditorController::Activate(TerrainTypeEditorWidget* terrainTypeEditorWidget)
{
	QString iAmHere;
}

void EditorController::Activate(UnitTypeEditorWidget* unitTypeEditorWidget)
{
	QString iAmHere;
}
