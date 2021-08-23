#include "stdafx.h"
#include "BaseEditor.h"

BaseEditor::BaseEditor(QObject *parent)
	: QObject(parent),
	Active(false)
{

}

void BaseEditor::SetActive(bool active)
{
	Active = active;
}

bool BaseEditor::GetActive() const
{
	return Active;
}
