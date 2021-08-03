#include "stdafx.h"
#include "ModelMapItem.h"

ModelMapItem::ModelMapItem( int row, int col, int id )
	: CenterPoint(0,0),
		Row(row),
		Col(col),
		Id(id),
		TerrainType(nullptr),
		OwnerType(nullptr)
{
}

ModelMapItem::~ModelMapItem()
{
}

void ModelMapItem::SetModelTerrainType(const ModelTerrainType *type)
{
	TerrainType = type;
}

const ModelTerrainType* ModelMapItem::GetTerrainType() const
{
	return TerrainType;
}

const int ModelMapItem::GetId() const
{
	return Id;
}

const int ModelMapItem::GetRow() const
{
	return Row;
}

const int ModelMapItem::GetCol() const
{
	return Col;
}

bool ModelMapItem::operator<(const ModelMapItem& rhs) const
{
	return Id < rhs.Id;
}
