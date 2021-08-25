#include "stdafx.h"
#include "GameUnitItem.h"
#include "model/ModelUnitType.h"

GameUnitItem::GameUnitItem(int gameUnitId)
	: Id(gameUnitId),
		UnitType(nullptr),
		OwnerType(nullptr),
		MapItem(nullptr),
		UnitTypeId(-1),
		OwnerTypeId(-1),
		MapItemId(-1)
{
}

GameUnitItem::~GameUnitItem()
{
}

const ModelUnitType* GameUnitItem::GetModelUnitType() const
{
	return UnitType;
}

const ModelOwnerType* GameUnitItem::GetModelOwnerType() const
{
	return OwnerType;
}

const GameMapItem* GameUnitItem::GetGameMapItem() const
{
	return MapItem;
}

const int GameUnitItem::GetId() const
{
	return Id;
}

const QString& GameUnitItem::GetName() const
{
	return Name;
}

void GameUnitItem::SetName(const QString& name)
{
	Name = name;
}

int GameUnitItem::GetModelUnitTypeId() const
{
	return UnitTypeId;
}

int GameUnitItem::GetModelOwnerTypeId() const
{
	return OwnerTypeId;
}

int GameUnitItem::GetGameMapItemId() const
{
	return MapItemId;
}

void GameUnitItem::UpdateTurn()
{
	//TODO: Reset movement points
	//TODO: Heal Unit
	//TODO: ...
}

bool GameUnitItem::CanOccupieCity() const
{
	return UnitType->GetCanOccupieCity();
}

bool GameUnitItem::operator<(const GameUnitItem& rhs) const
{
	return Id < rhs.Id;
}
