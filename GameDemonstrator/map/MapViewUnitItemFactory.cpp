#include "stdafx.h"
#include "MapViewUnitItemFactory.h"
#include "MapViewUnitItem.h"

MapViewUnitItemFactory* MapViewUnitItemFactory::Instance = nullptr; 

MapViewUnitItemFactory* MapViewUnitItemFactory::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new MapViewUnitItemFactory;
	return Instance;
}

void MapViewUnitItemFactory::Release()
{
	delete Instance;
	Instance = nullptr;
}

MapViewUnitItemFactory::MapViewUnitItemFactory()
{
}

MapViewUnitItemFactory::~MapViewUnitItemFactory()
{
}

MapViewUnitItem* MapViewUnitItemFactory::CreateDummyUnitItem()
{
	MapViewUnitItem* dummyUnitItem = new MapViewUnitItem();
	return dummyUnitItem;
}
