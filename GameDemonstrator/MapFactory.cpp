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

void MapFactory::SetMapView(MapView* mapView)
{
	MapViewInstance = mapView;
}

void MapFactory::SetParent(QObject *parent)
{
	Parent = parent;
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

void MapFactory::Release()
{
	delete Instance;
	Instance = nullptr;
}
