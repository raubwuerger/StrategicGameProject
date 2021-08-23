#include "stdafx.h"
#include "CityTypeEditor.h"
#include "model\ModelCityTypeRepository.h"
#include "model\ModelCityType.h"
#include "controller\EditorController.h"

CityTypeEditor::CityTypeEditor(QObject *parent)
	: BaseEditor(parent),
	EditorControllerInstance(nullptr),
	ActiveModelCityType(nullptr)
{

}

void CityTypeEditor::SetEditorController(EditorController* editorController)
{
	EditorControllerInstance = editorController;
}

void CityTypeEditor::SlotDeactivated()
{
	return; //TODO: Do nothing at the moment
}

void CityTypeEditor::SlotActivated()
{
	if (nullptr == EditorControllerInstance)
	{
		return;
	}
	EditorControllerInstance->Activate(this);
}

void CityTypeEditor::SlotActiveCityTypeId(int CityTypeId)
{
	ActiveModelCityType = ModelCityTypeRepository::GetInstance()->GetTypeById(CityTypeId);
}

void CityTypeEditor::SlotAddCity(int mapItemId)
{
	if (false == BaseEditor::GetActive())
	{
		return;
	}


}

void CityTypeEditor::SlotDeleteCity(int cityTypeId)
{
	if (false == BaseEditor::GetActive())
	{
		return;
	}
}
