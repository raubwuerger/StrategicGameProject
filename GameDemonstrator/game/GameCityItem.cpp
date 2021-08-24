#include "stdafx.h"
#include "GameCityItem.h"

GameCityItem::GameCityItem(int id)
	: Id(id),
		OwnerType(nullptr),
		MapItem(nullptr),
		OwnerTypeId(-1),
		MapItemId(-1),
		Efficiency(-1),
		SpezializedUnitTypeId(-1)
{
}

GameCityItem::~GameCityItem()
{
}

const int GameCityItem::GetId() const
{
	return Id;
}

const QString& GameCityItem::GetName() const
{
	return Name;
}

void GameCityItem::SetName(const QString& name)
{
	Name = name;
}

const ModelOwnerType* GameCityItem::GetModelOwnerType() const
{
	return OwnerType;
}

const GameMapItem* GameCityItem::GetGameMapItem() const
{
	return MapItem;
}

int GameCityItem::GetModelOwnerTypeId() const
{
	return OwnerTypeId;
}

int GameCityItem::GetGameMapItemId() const
{
	return MapItemId;
}

const ModelCityType* GameCityItem::GetCityModelType() const
{
	return CityType;
}

int GameCityItem::GetCityTypeId() const
{
	return CityTypeId;
}

void GameCityItem::UpdateTurn()
{
	//TODO: Increase build unit step
	//TODO: ...
}

int GameCityItem::GetEfficiency() const
{
	return Efficiency;
}

int GameCityItem::GetSpezializedUnitTypeId() const
{
	return SpezializedUnitTypeId;
}

bool GameCityItem::operator<(const GameCityItem& rhs) const
{
	return Id < rhs.Id;
}
