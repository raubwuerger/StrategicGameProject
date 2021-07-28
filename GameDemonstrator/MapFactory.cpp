#include "stdafx.h"
#include "MapFactory.h"
#include "CreateNewMap.h"
#include "QObject.h"
#include "LogInterface.h"

MapFactory* MapFactory::Instance = nullptr;

MapFactory* MapFactory::GetInstance()
{
	//TODO: Lock this code
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new MapFactory;
	return Instance;
}


CreateNewMap* MapFactory::CreateNewMapFunction()
{
	if( nullptr == Parent )
	{
		jha::GetLog()->Log( "Handover parameter <parent> is null!", jha::LOGLEVEL::LL_ERROR );
		return nullptr;
	}

	TheCreateNewMap = new CreateNewMap(Parent);
	return TheCreateNewMap;
}

MapFactory::MapFactory()
	: TheCreateNewMap(nullptr)
{
}

MapFactory::~MapFactory()
{
}

CreateNewMap* MapFactory::CreateNewMapAction( QObject *parent, QAction *action, MapView *mapView, const TerrainType *defaultTerrainType )
{
	return nullptr;
}

void MapFactory::SetMapView(MapView* mapView)
{
	MapViewInstance = mapView;
}

void MapFactory::SetParent(QObject *parent)
{
	Parent = parent;
}
