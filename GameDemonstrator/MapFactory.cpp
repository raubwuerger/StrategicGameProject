#include "stdafx.h"
#include "MapFactory.h"
#include "CreateNewMap.h"
#include "QObject.h"
#include "LogInterface.h"

using namespace jha;

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
		GetLog()->Log_ERROR( QObject::tr("Member <QObject Parentis null! -> SetParent()"));
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
