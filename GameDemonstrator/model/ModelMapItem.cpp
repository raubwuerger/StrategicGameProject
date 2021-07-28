#include "stdafx.h"
#include "ModelMapItem.h"

ModelMapItem::ModelMapItem( int row, int col )
	: CenterPoint(0,0),
		Row(row),
		Col(col),
		Type(nullptr),
		Owner(nullptr)
{
}

ModelMapItem::~ModelMapItem()
{
}
