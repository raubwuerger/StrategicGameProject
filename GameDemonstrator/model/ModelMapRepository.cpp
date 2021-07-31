#include "stdafx.h"
#include "ModelMapRepository.h"
#include "ModelMapItem.h"
#include "LogInterface.h"

ModelMapRepository*	ModelMapRepository::Instance = nullptr;

ModelMapRepository* ModelMapRepository::GetInstance()
{
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new ModelMapRepository;
	return Instance;
}

void ModelMapRepository::Release()
{

}

const QVector< QVector<ModelMapItem*> >* ModelMapRepository::GetMapItems() const
{
	return MapItems;
}

void ModelMapRepository::SetMapItems( const QVector< QVector<ModelMapItem*>>* mapItems)
{
	MapItems = mapItems;
}

ModelMapRepository::ModelMapRepository()
{
}

ModelMapRepository::~ModelMapRepository()
{
	delete MapItems;
}

int ModelMapRepository::GetCols() const
{
	if( nullptr == MapItems )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapItems()" ) );
		return 0;
	}

	QVector<ModelMapItem*> firstRow = MapItems->at(0);
	if( true == firstRow.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapItems()" ) );
		return 0;
	}

	return firstRow.size();
}

int ModelMapRepository::GetRows() const
{
	if( nullptr == MapItems )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapItems()" ) );
		return 0;
	}
	return MapItems->size();
}
