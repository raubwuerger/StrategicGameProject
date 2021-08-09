#include "stdafx.h"
#include "UnitTypeEditor.h"

UnitTypeEditor::UnitTypeEditor(QObject *parent)
{

}

UnitTypeEditor::~UnitTypeEditor()
{

}

void UnitTypeEditor::SetMapEventManager(MapEventManager* mapEventManager)
{
	MapEventManagerInstance = mapEventManager;
}

