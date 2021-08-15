#include "stdafx.h"
#include "TerrainTypeEditorWidget.h"
#include "controller/EditorController.h"

TerrainTypeEditorWidget::TerrainTypeEditorWidget(EditorController* editorController)
	: EditorControllerInstance(editorController)
{

}

void TerrainTypeEditorWidget::SlotActivated()
{
	EditorControllerInstance->Activate(this);
}
