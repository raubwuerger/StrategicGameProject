#include "stdafx.h"
#include "ModelMapItem.h"

ModelMapItem::ModelMapItem( int row, int col )
	: CenterPoint(0,0),
		Row(row),
		Col(col),
		Id(row*col+col),
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
