#include "stdafx.h"
#include "MapUnitItemFactory.h"
#include "MapUnitItem.h"

MapUnitItemFactory::MapUnitItemFactory()
{
}

MapUnitItemFactory::~MapUnitItemFactory()
{
}

MapUnitItem* MapUnitItemFactory::CreateDummyUnitItem()
{
	MapUnitItem* dummyUnitItem = new MapUnitItem( QPointF(64,121) );
	return dummyUnitItem;
}
