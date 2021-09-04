#include "stdafx.h"
#include "GameOwnerItem.h"
#include "model\ModelOwnerType.h"

GameOwnerItem::GameOwnerItem(int id)
	: Id(id),
	ModelOwnerTypeObject(nullptr),
	ModelOwnerTypeId(NOT_INITIALIZED_INT),
	Name(NOT_INITIALIZED_STRING),
	IsHuman(NOT_INITIALIZED_BOOL)
{

}

QColor GameOwnerItem::GetColor() const
{
	return ModelOwnerTypeObject->GetColor();
}

bool GameOwnerItem::operator==(const GameOwnerItem& rhs) const
{
	return this->Id == rhs.Id;
}
