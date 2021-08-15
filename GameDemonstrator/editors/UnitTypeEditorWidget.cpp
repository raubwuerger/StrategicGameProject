#include "stdafx.h"
#include "UnitTypeEditorWidget.h"
#include "controller/EditorController.h"

UnitTypeEditorWidget::UnitTypeEditorWidget(EditorController* editorController)
	: EditorControllerInstance(editorController)
{

}

void UnitTypeEditorWidget::SlotActivated()
{
	EditorControllerInstance->Activate(this);
}
