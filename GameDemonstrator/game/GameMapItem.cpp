#include "stdafx.h"
#include "GameMapItem.h"

GameMapItem::GameMapItem( int row, int col, int id )
	: 	Row(row),
		Col(col),
		Id(id),
		ModelTerrainTypeId(NOT_INITIALIZED_INT),
		TerrainType(nullptr),
		OwnerType(nullptr)
{
}

GameMapItem::~GameMapItem()
{
}

void GameMapItem::SetModelTerrainType(const ModelTerrainType *type)
{
	TerrainType = type;
}

const ModelTerrainType* GameMapItem::GetTerrainType() const
{
	return TerrainType;
}

const ModelOwnerType* GameMapItem::GetOwnerType() const
{
	return OwnerType;
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

int GameMapItem::GetModelTerrainTypeId() const
{
	return ModelTerrainTypeId;
}

void GameMapItem::SetModelTerrainTypeId(int modelTerrainTypeId)
{
	ModelTerrainTypeId = modelTerrainTypeId;
}

bool GameMapItem::operator<(const GameMapItem& rhs) const
{
	return Id < rhs.Id;
}
