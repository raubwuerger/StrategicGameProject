#include "stdafx.h"
#include "GameUnitItem.h"

GameUnitItem::GameUnitItem(int gameUnitId)
	: Id(gameUnitId),
		UnitType(nullptr)
{
}

GameUnitItem::~GameUnitItem()
{
}

void GameUnitItem::SetModelUnitType( const ModelUnitType *type )
{
	UnitType = type;
}

const ModelUnitType* GameUnitItem::GetModelUnitType() const
{
	return UnitType;
}

const int GameUnitItem::GetId() const
{
	return Id;
}

int GameUnitItem::GetGameMapItemId() const
{
	return GameMapItemId;
}

void GameUnitItem::SetGameMapItemId(int val)
{
	GameMapItemId = val;
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
