#include "stdafx.h"
#include "GameMapTile.h"

GameMapTile::GameMapTile( int row, int col, int id )
	: 	Row(row),
		Col(col),
		Id(id),
		ModelTerrainTypeId(NOT_INITIALIZED_INT),
		ModelOwnerTypeId(NOT_INITIALIZED_INT),
		TerrainTypeObject(nullptr),
		OwnerTypeObject(nullptr)
{
}

GameMapTile::~GameMapTile()
{
}

const ModelTerrainType* GameMapTile::GetTerrainType() const
{
	return TerrainTypeObject;
}

const ModelOwnerType* GameMapTile::GetOwnerType() const
{
	return OwnerTypeObject;
}

int GameMapTile::GetModelOwnerTypeId() const
{
	return ModelTerrainTypeId;
}

const int GameMapTile::GetId() const
{
	return Id;
}

const int GameMapTile::GetRow() const
{
	return Row;
}

const int GameMapTile::GetCol() const
{
	return Col;
}

void GameMapTile::SetModelTerrainType(const ModelTerrainType* modelTerrainType)
{
	Q_ASSERT(modelTerrainType);
	TerrainTypeObject = modelTerrainType;
}

void GameMapTile::SetModelTerrainTypeId(int id)
{
	ModelTerrainTypeId = id;
}

int GameMapTile::GetModelTerrainTypeId() const
{
	return ModelTerrainTypeId;
}

bool GameMapTile::operator<(const GameMapTile& rhs) const
{
	return Id < rhs.Id;
}
