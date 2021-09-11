#include "stdafx.h"
#include "GameOwner.h"
#include "model\ModelOwnerType.h"

GameOwner::GameOwner(int id)
	: Id(id),
	ModelOwnerTypeObject(nullptr),
	ModelOwnerTypeId(NOT_INITIALIZED_INT),
	Name(NOT_INITIALIZED_STRING),
	IsHuman(NOT_INITIALIZED_BOOL)
{

}

QColor GameOwner::GetColor() const
{
	return ModelOwnerTypeObject->GetColor();
}

bool GameOwner::operator==(const GameOwner& rhs) const
{
	return this->Id == rhs.Id;
}
