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

bool GameUnitItem::operator<(const GameUnitItem& rhs) const
{
	return Id < rhs.Id;
}
