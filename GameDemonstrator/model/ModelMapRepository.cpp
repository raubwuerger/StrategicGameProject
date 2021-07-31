#include "stdafx.h"
#include "ModelMapRepository.h"
#include "ModelMapItem.h"

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
	MapItems = MapItems;
}

ModelMapRepository::ModelMapRepository()
{
}

ModelMapRepository::~ModelMapRepository()
{
	delete MapItems;
}
