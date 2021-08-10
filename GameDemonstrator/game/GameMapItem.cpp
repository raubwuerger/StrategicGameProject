#include "stdafx.h"
#include "GameMapItem.h"

GameMapItem::GameMapItem( int row, int col, int id )
	: CenterPoint(0,0),
		Row(row),
		Col(col),
		Id(id),
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

bool GameMapItem::operator<(const GameMapItem& rhs) const
{
	return Id < rhs.Id;
}