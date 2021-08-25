#include "stdafx.h"
#include "ModelUnitType.h"

ModelUnitType::ModelUnitType(int id)
	:Id(id),
	Name(NOT_INITIALIZED_STRING),
	PictureName(NOT_INITIALIZED_STRING),
	Image(nullptr),
	Strength(NOT_INITIALIZED_INT),
	Range(NOT_INITIALIZED_INT),
	MovementPoints(NOT_INITIALIZED_INT),
	CanOccupieCity(NOT_INITIALIZED_BOOL),
	GetCounterattack(NOT_INITIALIZED_BOOL)
{
}

int ModelUnitType::GetId() const
{
	return Id;
}

void ModelUnitType::SetName(const QString& name)
{
	Name = name;
}

const QImage* ModelUnitType::GetImage() const
{
	return Image;
}

const QString& ModelUnitType::GetName() const
{
	return Name;
}

const QString& ModelUnitType::GetPictureName() const
{
	return PictureName;
}

bool ModelUnitType::IsTerrainTypeAccessible(int terrainTypeId) const
{
	return AccessibleTerrainTypes.contains(terrainTypeId);
}

bool ModelUnitType::IsUnitTypeRecognisable(int modelUnitTypeId) const
{
	return RecognisableUnitTypes.contains(modelUnitTypeId);
}

bool ModelUnitType::IsUnitTypeAttackable(int modelUnitTypeId) const
{
	return AttackableUnitTypes.contains(modelUnitTypeId);
}
