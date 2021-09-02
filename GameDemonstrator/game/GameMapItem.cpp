#include "stdafx.h"
#include "GameMapItem.h"

GameMapItem::GameMapItem( int row, int col, int id )
	: 	Row(row),
		Col(col),
		Id(id),
		ModelTerrainTypeId(NOT_INITIALIZED_INT),
		ModelOwnerTypeId(NOT_INITIALIZED_INT),
		TerrainTypeObject(nullptr),
		OwnerTypeObject(nullptr)
{
}

GameMapItem::~GameMapItem()
{
}

const ModelTerrainType* GameMapItem::GetTerrainType() const
{
	return TerrainTypeObject;
}

const ModelOwnerType* GameMapItem::GetOwnerType() const
{
	return OwnerTypeObject;
}

int GameMapItem::GetModelOwnerTypeId() const
{
	return ModelTerrainTypeId;
}

const int GameMapItem::GetId() const
{
	return Id;
}

const int GameMapItem::GetRow() const
{
	return Row;
}

const int GameMapItem::GetCol() const
{
	return Col;
}

void GameMapItem::SetTerrainTypeObject(const ModelTerrainType* modelTerrainType)
{
	TerrainTypeObject = modelTerrainType;
}

int GameMapItem::GetModelTerrainTypeId() const
{
	return ModelTerrainTypeId;
}

bool GameMapItem::operator<(const GameMapItem& rhs) const
{
	return Id < rhs.Id;
}
