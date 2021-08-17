#include "stdafx.h"
#include "GameUnitItem.h"

GameUnitItem::GameUnitItem(int gameUnitId)
	: Id(gameUnitId),
		UnitType(nullptr),
		OwnerType(nullptr)
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

const int GameUnitItem::GetId() const
{
	return Id;
}

void GameUnitItem::SetGameMapItemId(int gameMapUnitId)
{
	GameMapItemId = gameMapUnitId;
}

int GameUnitItem::GetGameMapItemId() const
{
	return GameMapItemId;
}

const QString& GameUnitItem::GetName() const
{
	return Name;
}

void GameUnitItem::SetName(const QString& name)
{
	Name = name;
}

bool GameUnitItem::operator<(const GameUnitItem& rhs) const
{
	return Id < rhs.Id;
}
