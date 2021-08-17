#include <stdafx.h>
#include "OwnerTypeEditor.h"
#include "model\ModelOwnerTypeRepository.h"
#include "model\ModelOwnerType.h"
#include "controller\EditorController.h"

OwnerTypeEditor::OwnerTypeEditor(QObject *parent)
	: BaseEditor(parent),
	EditorControllerInstance(nullptr),
	ActiveModelOwnerType(nullptr)
{

}

void OwnerTypeEditor::SetEditorController(EditorController* editorController)
{
	EditorControllerInstance = editorController;
}

void OwnerTypeEditor::SlotActivated()
{
	if (nullptr == EditorControllerInstance)
	{
		return;
	}
	EditorControllerInstance->Activate(this);
}

void OwnerTypeEditor::SlotActiveOwnerTypeId(int ownerTypeId)
{
	ActiveModelOwnerType = ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(ownerTypeId);
}
