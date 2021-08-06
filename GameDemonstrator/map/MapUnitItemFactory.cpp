#include "stdafx.h"
#include "MapUnitItemFactory.h"
#include "MapUnitItem.h"

MapUnitItemFactory* MapUnitItemFactory::Instance = nullptr; 

MapUnitItemFactory* MapUnitItemFactory::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new MapUnitItemFactory;
	return Instance;
}

void MapUnitItemFactory::Release()
{
	delete Instance;
	Instance = nullptr;
}

MapUnitItemFactory::MapUnitItemFactory()
{
}

MapUnitItemFactory::~MapUnitItemFactory()
{
}

MapUnitItem* MapUnitItemFactory::CreateDummyUnitItem()
{
	MapUnitItem* dummyUnitItem = new MapUnitItem();
	return dummyUnitItem;
}
